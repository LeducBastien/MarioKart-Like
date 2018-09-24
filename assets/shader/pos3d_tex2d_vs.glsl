#version 420

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3	vertex_pos;
in vec2 vertex_texcoord;

out vec2 texcoord;

void	main(void)
{
	gl_Position = proj * view * model * vec4(vertex_pos, 1.0);
	texcoord = vertex_texcoord;
}
