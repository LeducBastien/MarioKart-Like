#version 420

uniform sampler2D	sampler;

in vec2		texcoord;

out	vec4	out_color;

void	main(void)
{
	out_color = texture(sampler, texcoord);
}
