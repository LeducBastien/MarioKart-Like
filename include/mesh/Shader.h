#ifndef __SHADER_H_INCLUDED__
#define __SHADER_H_INCLUDED__

#include <SDL.h>
#include <GL/glew.h>
#include <string>

namespace id
{
	class Shader
	{
	public:
		Shader() = default;
		Shader(Shader const&) = delete;
		Shader(Shader&&) = delete;
		~Shader();

		auto operator=(Shader const&) -> Shader* = delete;
		auto operator=(Shader&&) -> Shader* = delete;

		GLuint getVertexShader() const& {return this->vs_id;}
		GLuint getFragmentShader() const& {return this->fs_id;}

		static auto load(std::string const&, Shader* shader = nullptr) -> Shader*;

		auto loadShader(std::string const&,GLint) -> GLuint;
	private:

		GLuint vs_id;
		GLuint fs_id;
	};
}
#endif
