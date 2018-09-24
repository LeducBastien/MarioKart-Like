#ifndef __PROGRAM_H_INCLUDED__
#define __PROGRAM_H_INCLUDED__

#include <SDL.h>
#include <GL/glew.h>
#include <string>
#include "Log.h"

namespace id
{
	class Shader;

	class Program
	{
	public:
		Program(Program const&) = delete;
		Program(Program&&) = delete;
		~Program();

		auto operator=(Program const&) -> Program& = delete;
		auto operator=(Program&&) -> Program& = delete;

		GLuint getProgramID() const& {return this->prg_id;}
		std::string getFlag() const& {return this->flag;}

		void setProgramID(GLuint new_prg) {prg_id = new_prg;}

		static auto create(Shader*, std::string const&, Program* prog = nullptr) -> Program*;

		auto load(GLuint, GLuint) -> GLuint;

		GLuint use();
	private:
		Program() = default;

		GLuint prg_id;

		std::string flag;
	};
}

#endif
