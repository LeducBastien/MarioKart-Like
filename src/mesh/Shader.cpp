#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <fstream>

#include "Shader.h"

namespace id
{
	Shader::~Shader()
	{
		glDeleteShader(this->vs_id);
		glDeleteShader(this->fs_id);
	}

	auto Shader::load(std::string const& name, Shader* shader) -> Shader*
	{
		if(shader == nullptr)
		shader = new Shader;

		shader->vs_id = shader->loadShader(name, GL_VERTEX_SHADER);
                shader->fs_id = shader->loadShader(name, GL_FRAGMENT_SHADER);

		return shader;
	}

	auto    Shader::loadShader(std::string const& name, GLint shader_type) -> GLuint
        {
                // ouvrir le ficher avec fstream
                std::string filename("./assets/shader/"+ name);

                if (shader_type == GL_VERTEX_SHADER)
                        filename += "_vs.glsl";

                else
                        filename += "_fs.glsl";

                std::ifstream file;
                std::string source_code;

                file.open(filename, std::ios::binary);
                SDL_assert(file.is_open());

                file.seekg(0, std::ios::end);
                auto file_len = file.tellg();
                file.seekg(0, std::ios::beg);

                source_code.resize(file_len);
                file.read(&source_code[0], file_len);
                file.close();


                auto vs_id = glCreateShader(shader_type);

                char const* c_source = source_code.c_str();
                int const source_len = source_code.size();
                glShaderSource(vs_id, 1, &c_source, &source_len);

                glCompileShader(vs_id);

                GLint status;
                glGetShaderiv(vs_id, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
                {
                        GLint len;
                        glGetShaderiv(vs_id, GL_INFO_LOG_LENGTH, &len);

                        auto infolog = new char [len];
                        glGetShaderInfoLog(vs_id, len , &len, infolog);
                        std::cerr << "Shader [ "<< filename <<"] compile error: " << infolog <<std::endl;
                        SDL_assert(false);
                }
//                else
//                        std::cout << "Shader [ " << filename <<" ] compilation success " << std::endl;




                return vs_id;
        }

}
