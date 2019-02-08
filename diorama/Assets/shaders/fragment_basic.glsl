#version 330 core
out vec4 color;

in vec3 frag_position;
in vec4 frag_color;
in vec2 frag_tex_coord;

void main()
{
	color.rgb = abs(frag_position);
//	color = frag_color;
}
