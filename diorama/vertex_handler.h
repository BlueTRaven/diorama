#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

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

struct mat4x4
{
	float a, b, c, d,
		  e, f, g, h,
		  i, j, k, l,
		  m, n, o, p;

	mat4x4()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;

		e = 0;
		f = 0;
		g = 0;
		h = 0;
		
		i = 0;
		j = 0;
		k = 0;
		l = 0;

		m = 0;
		n = 0;
		o = 0;
		p = 0;			
	}

	mat4x4(float _a, float _b, float _c, float _d, 
		   float _e, float _f, float _g, float _h, 
		   float _i, float _j, float _k, float _l, 
		   float _m, float _n, float _o, float _p)
	{
		a = _a;
		b = _b;
		c = _c;
		d = _d;

		e = _e;
		f = _f;
		g = _g;
		h = _h;
		
		i = _i;
		j = _j;
		k = _k;
		l = _l;

		m = _m;
		n = _n;
		o = _o;
		p = _p;
	}
};

mat4x4 get_identity();

void init_vertex_buffers();

GLint vertex_attribute(GLint program, const char * name, GLint fields, GLsizei size, void * offset);

GLint uniform_float(GLint program, const char * name, float value);

GLint uniform_mat4(GLint program, const char * name, GLsizei count, GLboolean transpose, const GLfloat * value);

float * mat4x4_to_array(mat4x4 matrix);

