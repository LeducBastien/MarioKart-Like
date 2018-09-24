#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

#include "Tools.h"
#include "ModelMesh.h"

namespace id
{
	ModelMesh::ModelMesh()
	{
	}

	ModelMesh::~ModelMesh()
	{
		IMG_Quit();

		if (this->tex_id != 0)
			glDeleteTextures(1, &this->tex_id);

		this->mv.clear();
		this->mvt.clear();
		this->mf.clear();
		this->draw_coord.clear();
	}

	auto ModelMesh::create(std::string const& name, std::string const& texture) -> ModelMesh*
	{

		ModelMesh* mesh = new ModelMesh();

		mesh->log.setIdentifier("ModelMesh");
		mesh->log.setOutput(id::log::BOTH);

		if(name == "" && texture == "")
			return mesh;

		else if(name != "" && texture == "")
		{
			if (name.rfind("./assets/") == std::string::npos)
				mesh->filename = "./assets/" + name;
			else
				mesh->filename = name;
			mesh->loadModel();
			mesh->model_only = true;
			return mesh;
		}

		else
		{
			if (name.rfind("./assets/") == std::string::npos)
                                mesh->filename = "./assets/" + name;
                        else
                                mesh->filename = name;
		}

		if (texture.rfind("./assets/") == std::string::npos)
			mesh->texture = "./assets/" + texture;
		mesh->setTexture();
		mesh->loadModel();	

		return mesh;
	}

	void ModelMesh::loadModel()
	{
		std::ifstream file;

		file.open(this->filename, std::ios::binary);

		if (!file.is_open())
		{
			this->log.error("Cannot open model : file does not exist");
			return;
		}

		file.seekg(0, std::ios::end);
		auto file_len = file.tellg();
                file.seekg(0, std::ios::beg);

		int cur_pos = 0;

		std::string line;

		while(cur_pos < file_len)
		{

			std::getline(file, line);

			this->getCoordinates(line);

			cur_pos = file.tellg();
		}

		this->setGLPointers();
	}

	void ModelMesh::setTexture()
	{
		SDL_Surface* surf = IMG_Load(this->texture.c_str());

		if (!surf)
		{
			this->log.error("Cannot load texture : file does not exist");
			return;
		}

		glGenTextures(1, &this->tex_id); 
		glBindTexture(GL_TEXTURE_2D, this->tex_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
		
		SDL_FreeSurface(surf);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void ModelMesh::getCoordinates(std::string const& line)
	{

		switch(line[0])
		{
			case 'v':
				this->getVVT(line);
			break;

			case 'f':
				this->getF(line);
			break;
		}
	}

	void ModelMesh::getVVT(std::string const& line)
	{

		std::vector<std::string> str_array = Tools::explodeString(line, ' ');
		std::vector<std::string>::iterator first = str_array.begin();
		std::vector<std::string>::iterator last = str_array.end();

		if (first != last)
		{
			switch(line[1])
			{
				case ' ':
				{
					Model_v mv;
					mv.x = stof(str_array[1]);
					mv.y = stof(str_array[2]);
					mv.z = stof(str_array[3]);

					this->mv.push_back(mv);
				
				}
				break;

				case 't':
				{
                                        Model_vt mvt;
                                        mvt.x = stof(str_array[1]);
                                        mvt.y = stof(str_array[2]);

					this->mvt.push_back(mvt);
				}
				break;

				default: break;
			}
		}
	}

	void ModelMesh::getF(std::string const& line)
	{
		if (line[1] != ' ')
			return;

		std::vector<std::string> str_array = Tools::explodeString(line, ' ');
                std::vector<std::string>::iterator first = str_array.begin();
                std::vector<std::string>::iterator last = str_array.end();

		if( first != last )
		{
			std::vector<std::string> f1 = Tools::explodeString( str_array[1], '/');
			std::vector<std::string> f2 = Tools::explodeString( str_array[2], '/');
			std::vector<std::string> f3 = Tools::explodeString( str_array[3], '/');

			Model_f mf;
			mf.v1 = std::stoul(f1[0]);
			mf.v2 = std::stoul(f2[0]);
			mf.v3 = std::stoul(f3[0]);

			mf.vt1 = std::stoul(f1[1]);
			mf.vt2 = std::stoul(f2[1]);
			mf.vt3 = std::stoul(f3[1]);
			
			this->mf.push_back(mf);
		}

	}

	void ModelMesh::setGLPointers()
	{
		std::vector<Model_f>::iterator first = this->mf.begin();
		std::vector<Model_f>::iterator last = this->mf.end();

		for (; first != last; ++first)
		{
			this->addVertexCoord(*first);
		}
	}

	void ModelMesh::addVertexCoord(Model_f mf)
	{
		Model_v v1 = this->mv[mf.v1 - 1];
		Model_v v2 = this->mv[mf.v2 - 1];
		Model_v v3 = this->mv[mf.v3 - 1];

		Model_vt vt1 = this->mvt[mf.vt1 - 1];
		Model_vt vt2 = this->mvt[mf.vt2 - 1];
		Model_vt vt3 = this->mvt[mf.vt3 - 1];

		this->addPoint(v1, vt1);
		this->addPoint(v2, vt2);
		this->addPoint(v3, vt3);
	}

	void ModelMesh::addPoint(Model_v const& mv, Model_vt const& mvt)
	{
		this->draw_coord.push_back(mv.x);
		this->draw_coord.push_back(mv.y);
		this->draw_coord.push_back(mv.z);
		this->draw_coord.push_back(mvt.x);
        	this->draw_coord.push_back(-mvt.y);

		++(this->nb_points);
	}

	void ModelMesh::draw()
        {
		glBindTexture(GL_TEXTURE_2D, this->tex_id);

                glDrawArrays(GL_TRIANGLES, 0, this->nb_points);

		glBindTexture(GL_TEXTURE_2D, 0);
        }
}
