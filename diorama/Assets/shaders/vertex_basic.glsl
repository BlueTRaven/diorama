#version 330 core


in vec3 position;
in vec2 tex_coord;
in vec4 color;

out vec2 frag_tex_coord;
out vec4 frag_color;

void main()
{
	gl_Position = vec4(position, 1.0);

	frag_tex_coord = tex_coord;
	frag_color = color;
}

