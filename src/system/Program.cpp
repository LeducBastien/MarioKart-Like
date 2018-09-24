#include <iostream>
#include <string>

#include "Shader.h"
#include "Program.h"

namespace id
{
	Program::~Program()
	{
		glDeleteProgram(this->prg_id);
	}

	auto Program::create(Shader* shader, std::string const& name, Program* prog) -> Program*
	{
		SDL_assert(shader);

		if(prog == nullptr)
		prog = new Program();

		GLuint vs_id = shader->getVertexShader();
		GLuint fs_id = shader->getFragmentShader();
		prog->prg_id = prog->load(vs_id,fs_id);
		prog->flag = name;

		return prog;
	}
	auto Program::load(GLuint vs_id, GLuint fs_id) -> GLuint
        {
                auto    prg_id = glCreateProgram();

                glAttachShader(prg_id, vs_id);
                glAttachShader(prg_id ,fs_id);

                glLinkProgram(prg_id);

                GLint status;
                glGetProgramiv(prg_id, GL_LINK_STATUS, &status);

                if (status == GL_FALSE)
                {
                        GLint len;
                        glGetShaderiv(prg_id, GL_INFO_LOG_LENGTH, &len);

                        auto infolog = new char [len];
                        glGetProgramInfoLog(prg_id, len , &len, infolog);
                        SDL_assert(false);
                }
                
		glDetachShader(prg_id, vs_id);
                glDetachShader(prg_id, fs_id);

                glDeleteShader(vs_id);
                glDeleteShader(fs_id);

                return prg_id;

        }

	GLuint Program::use()
	{
		glUseProgram(this->prg_id);

		return this->prg_id;
	}
}
