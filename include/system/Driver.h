#ifndef __DRIVER_H_INCLUDED__
#define __DRIVER_H_INCLUDED__

#include <SDL.h>
#include <GL/glew.h>
#include <string>
#include <vector>

#include "maths/Matrix.h"
#include "Log.h"

namespace id
{
	class Shader;
	class Program;
	class SceneManager;

	class Driver
	{
	public:
		Driver(Driver const&) = delete;
		Driver(Driver&&) = delete;
		~Driver();

		auto operator=(Driver const&) -> Driver& = delete;
		auto operator=(Driver&&) -> Driver& = delete;

		auto getCurrentProgram() -> GLuint {return this->cur_prg_id;}
		std::vector<Program*> const  getProgramTab() {return prgs;}

		static Driver* create(SDL_Window*);

		GLuint addShader(std::string const&);

		auto loadShader(std::string const&, GLint shader_type) -> GLuint;
		GLuint ReplaceShader(std::string const& name, Shader* shader, Program* prg);
		GLuint getProgram(std::string const&);
		auto getProgramByID(GLuint const&) -> Program*;
		GLuint getVAO() {return this->vao;}
		GLuint getVBO() {return this->vbo;}

		void enableDepthTest();

		void useProgram(GLuint const&, SceneManager*);

		void update(SceneManager*);
		void close();
	private:
		Driver();

		id::log::Log log;

		std::vector<Program*> prgs;

		GLuint cur_prg_id;

		SDL_GLContext ctxt;

		GLuint vao;
		GLuint vbo;

		float angle;
	};

}
#endif
