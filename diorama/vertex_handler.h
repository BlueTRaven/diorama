#pragma once

struct vec2
{
	float x, y;

	vec2()
	{
		x = 0;
		y = 0;
	}

	vec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

struct vec3
{
	float x, y, z;

	vec3()
	{
		x = 0;
		y = 0; 
		z = 0;
	}

	vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

struct vec4
{
	float x, y, z, w;

	vec4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	vec4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};

struct Vertex
{
	vec3 position;
	vec2 tex_coords;
	vec4 color;

	//data is as such: 1.0f, 1.0f, 0.0f (pos), 0.0f, 0.0f (tex_coords), 1.0f, 1.0f, 1.0f, 1.0f (color)

	Vertex()
	{
		position = vec3();
		tex_coords = vec2();
		color = vec4();
	}	

	Vertex(vec3 _position)
	{
		position = _position;
	}
};

void init_vertex_buffers();
