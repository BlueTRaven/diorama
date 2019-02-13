#version 330 core
out vec4 color;

in vec4 frag_color;
in vec2 frag_tex_coord;

uniform sampler2D tex;

void main()
{
	//color = vec4(vec3(gl_FragCoord.z), 1.0);
	color = texture(tex, frag_tex_coord); 
}
