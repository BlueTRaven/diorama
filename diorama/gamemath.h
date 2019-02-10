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

	//bool valid;

	Vertex()
	{
		position = vec3();
		tex_coords = vec2();
		color = vec4();
	}	

	Vertex(vec3 _position)
	{
		position = _position;

		//valid = true;
	}

	Vertex(vec3 _position, vec2 _tex_coords, vec4 _color)
	{
		position = _position;
		tex_coords = _tex_coords;
		color = _color;

		//valid = true;
	}
};

struct mat4x4
{
	float m[16];

	mat4x4()
	{
		for (int i = 0; i < 16; i++)
			m[i] = 0;
	}
	
	mat4x4(float _a, float _b, float _c, float _d, 
		   float _e, float _f, float _g, float _h, 
		   float _i, float _j, float _k, float _l, 
		   float _m, float _n, float _o, float _p)
	{
		m[0] = _a;
		m[1] = _b;
		m[2] = _c;
		m[3] = _d;

		m[4] = _e;
		m[5] = _f;
		m[6] = _g;
		m[7] = _h;
		
		m[8] = _i;
		m[9] = _j;
		m[10] = _k;
		m[11] = _l;

		m[12] = _m;
		m[13] = _n;
		m[14] = _o;
		m[15] = _p;
	}
};

mat4x4 * get_identity();

mat4x4 * get_perspective(float width, float height, float z_near, float z_far, float fov);

float rad_to_deg(float radians);

float deg_to_rad(float degrees);
