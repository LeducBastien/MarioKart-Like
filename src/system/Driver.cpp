#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

#include "maths/tools.h"
#include "Shader.h"
#include "SceneManager.h"
#include "Program.h"
#include "Driver.h"

namespace id
{

	Driver::Driver()
	{
		vbo = 0;
		vao = 0;
		cur_prg_id = 0;
		angle = 0.f;
		ctxt = nullptr;
	}

	Driver::~Driver()
	{
		this->ctxt = nullptr;
	}

	Driver* Driver::create(SDL_Window* win)
	{
		auto* drv = new Driver();

		drv->ctxt = SDL_GL_CreateContext(win);
		SDL_assert(drv->ctxt);

		glewExperimental = GL_TRUE;
        	auto    status = glewInit();
	        SDL_assert(status == GLEW_OK);

		drv->log.setIdentifier("Driver");
		drv->log.setOutput(id::log::BOTH);
		drv->log.info("Initializing Driver");

        	// Enabling Depth settings
	        glEnable(GL_DEPTH_TEST);
        	glDepthMask(GL_TRUE);
	        glDepthFunc(GL_LESS);
	        glEnable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);

		glGenVertexArrays(1, &drv->vao);
                glGenBuffers(1,&drv->vbo);

                //glBindVertexArray(drv->vao);
                glBindBuffer(GL_ARRAY_BUFFER, drv->vbo);

		return drv;
	}

	GLuint Driver::addShader(std::string const& name)
	{
		GLuint prg_id = this->getProgram(name);

		if (prg_id != 0)
			return prg_id;

		auto* shader = Shader::load(name);
		auto* prg = Program::create(shader, name);

		delete shader;

		this->prgs.push_back(prg);

		return prg->use();
	}

	GLuint Driver::ReplaceShader(std::string const& name, Shader* shader, Program* prg)
	{
		GLuint prg_id = this->getProgram(name);
		
		shader = Shader::load(name, shader);
                prg = Program::create(shader, name, prg);
		
		unsigned int i = 0;

		delete shader;	
	
		if(prgs.size() == 1)
		{
			return addShader("color");
		}

		else
		while(i < prgs.size())
		{
			if(prg_id == prgs[i]->getProgramID())
			{
				prgs[i] = prg;
				return prgs[i]->use();
			}

			++i;
		}

		return prg->use();
		

	}

	GLuint Driver::getProgram(std::string const& flag)
	{
		std::vector<Program*>::iterator first = this->prgs.begin();
		std::vector<Program*>::iterator last = this->prgs.end();

		for (; first != last; ++first)
		{
			std::string prg_flag = (*first)->getFlag();
			if (flag == prg_flag)
			{
				GLuint prg_id = (*first)->getProgramID();
				return prg_id;
			}
		}

		return 0;
	}

	auto Driver::getProgramByID(GLuint const& search_id) -> Program*
	{
		std::vector<Program*>::iterator first = this->prgs.begin();
		std::vector<Program*>::iterator last = this->prgs.end();

		for (; first != last; ++first)
		{
			GLuint prg_id = (*first)->getProgramID();

			if (search_id == prg_id)
				return *first;
		}

		return nullptr;
	}

	void Driver::enableDepthTest()
	{
		glEnable(GL_CULL_FACE);
                glEnable(GL_DEPTH_TEST);
	}

	void Driver::useProgram(GLuint const& prg_id, SceneManager* scenemgr)
	{

		glUseProgram(0);

		auto* prg = this->getProgramByID(prg_id);

		if (prg)
		{
			this->cur_prg_id = prg->getProgramID();
			prg->use();

			scenemgr->switchShader();
		}
	}

	void Driver::update(SceneManager* scenemgr)
	{
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
               	scenemgr->update();
	}

	void Driver::close()
	{
		this->log.info("Closing Driver");

		glDeleteBuffers(1, &this->vbo);
                glDeleteBuffers(1, &this->vao);
		glDeleteVertexArrays(1, &this->vao);

		std::vector<Program*>::iterator first = this->prgs.begin();
                std::vector<Program*>::iterator last = this->prgs.end();

                for (; first != last; ++first)
                {
                        delete *first;
                }
		
                this->prgs.clear();

		SDL_GL_DeleteContext(this->ctxt);
	}
}
