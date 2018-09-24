#version 420

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3	vertex_pos;
out vec4 vertex_color;

out vec4 color;

void main(void)
{
	gl_Position = proj * view * model * vec4(vertex_pos, 1.0);
	color = vertex_color;
}
