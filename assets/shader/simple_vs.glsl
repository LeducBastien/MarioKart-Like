#version 420

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

in vec3 pos;
in vec2 texcoord;

out vec4 tmpColor;
out vec2 tmpTexcoord;

void main(void)
{
	gl_Position = proj * view * world * vec4(pos, 1);
	tmpTexcoord = texcoord;
}
