#pragma once

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

	const float operator[](int index) const
	{
		return m[index];
	}

	mat4x4 operator*(const mat4x4 matrix)
	{
		mat4x4 out = mat4x4();

 		out.m[0] = this->m[0] * matrix[0] + this->m[1] * matrix[4] + this->m[2] * matrix[8] + this->m[3] * matrix[12];
		out.m[1] = this->m[0] * matrix[1] + this->m[1] * matrix[5] + this->m[2] * matrix[9] + this->m[3] * matrix[13];
		out.m[2] = this->m[0] * matrix[2] + this->m[1] * matrix[6] + this->m[2] * matrix[10] + this->m[3] * matrix[14];
		out.m[3] = this->m[0] * matrix[3] + this->m[1] * matrix[7] + this->m[2] * matrix[11] + this->m[3] * matrix[15];

		out.m[4] = this->m[4] * matrix[0] + this->m[5] * matrix[4] + this->m[6] * matrix[8] + this->m[7] * matrix[12];
		out.m[5] = this->m[4] * matrix[1] + this->m[5] * matrix[5] + this->m[6] * matrix[9] + this->m[7] * matrix[13];
		out.m[6] = this->m[4] * matrix[2] + this->m[5] * matrix[6] + this->m[6] * matrix[10] + this->m[7] * matrix[14];
		out.m[7] = this->m[4] * matrix[3] + this->m[5] * matrix[7] + this->m[6] * matrix[11] + this->m[7] * matrix[15];
	
		out.m[8] = this->m[8] * matrix[0] + this->m[9] * matrix[4] + this->m[10] * matrix[8] + this->m[11] * matrix[12];
		out.m[9] = this->m[8] * matrix[1] + this->m[9] * matrix[5] + this->m[10] * matrix[9] + this->m[11] * matrix[13];
		out.m[10] = this->m[8] * matrix[2] + this->m[9] * matrix[6] + this->m[10] * matrix[10] + this->m[11] * matrix[14];
		out.m[11] = this->m[8] * matrix[3] + this->m[9] * matrix[7] + this->m[10] * matrix[11] + this->m[11] * matrix[15];

		out.m[12] = this->m[12] * matrix[0] + this->m[13] * matrix[4] + this->m[14] * matrix[8] + this->m[15] * matrix[12];
		out.m[13] = this->m[12] * matrix[1] + this->m[13] * matrix[5] + this->m[14] * matrix[9] + this->m[15] * matrix[13];
		out.m[14] = this->m[12] * matrix[2] + this->m[13] * matrix[6] + this->m[14] * matrix[10] + this->m[15] * matrix[14];
		out.m[15] = this->m[12] * matrix[3] + this->m[13] * matrix[7] + this->m[14] * matrix[11] + this->m[15] * matrix[15];

		return out;	
	}

	mat4x4 inverse();
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

	vec4(float val)
	{
		x = val;
		y = val;
		z = val;
		w = val;
	}

	vec4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vec4 operator-(const vec4 &right)
	{
		return vec4(this->x - right.x, this->y - right.y, this->z - right.z, this->w - right.w);
	}
	
	vec4 operator*(const vec4 &right)
	{
		return vec4(this->x * right.x, this->y * right.y, this->z * right.z, this->w * right.w);
	}

	vec4 operator*(const mat4x4 matrix)
	{
		return vec4(
			   matrix[0] * this->x + matrix[1] * this->x + matrix[2] * this->x + matrix[3] * this->x,
			   matrix[4] * this->y + matrix[5] * this->y + matrix[6] * this->y + matrix[7] * this->y,
			   matrix[8] * this->z + matrix[9] * this->z + matrix[10] * this->z + matrix[11] * this->z,
			   matrix[12] * this->w + matrix[13] * this->w + matrix[14] * this->w + matrix[15] * this->w);
	}

	friend vec4 operator*(mat4x4 matrix, const vec4 vec)
	{
		return vec4(
				vec.x * matrix[0] + vec.x * matrix[1] + vec.x * matrix[2] + vec.x * matrix[3],
				vec.y * matrix[4] + vec.y * matrix[5] + vec.y * matrix[6] + vec.y * matrix[7],
				vec.z * matrix[8] + vec.z * matrix[9] + vec.z * matrix[10] + vec.z * matrix[11],
				vec.w * matrix[12] + vec.w * matrix[13] + vec.w * matrix[14] + vec.w * matrix[15]);
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

	vec3(float val)
	{
		x = val;
		y = val;
		z = val;
	}

	vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float length();

	vec3 normalized();

	vec3 operator*(const vec3 &right)
	{
		return vec3(this->x * right.x, this->y * right.y, this->z * right.z);
	}

	vec3 operator*(const float scalar)
	{
		return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	vec3 operator*(const mat4x4 matrix)
	{
		vec4 vec = vec4(this->x, this->y, this->z, 1.0f);

		vec4 out = vec * matrix;
		return vec3(out.x, out.y, out.z);
	}

	friend vec4 operator*(mat4x4 matrix, const vec3 vector)
	{
		vec4 vec = vec4(vector.x, vector.y, vector.z, 1.0f);

		return vec4(
				vec.x * matrix[0] + vec.x * matrix[1] + vec.x * matrix[2] + vec.x * matrix[3],
				vec.y * matrix[4] + vec.y * matrix[5] + vec.y * matrix[6] + vec.y * matrix[7],
				vec.z * matrix[8] + vec.z * matrix[9] + vec.z * matrix[10] + vec.z * matrix[11],
				vec.w * matrix[12] + vec.w * matrix[13] + vec.w * matrix[14] + vec.w * matrix[15]);
	}

	vec3 operator+(const vec3 add)
	{
		return vec3(this->x + add.x, this->y + add.y, this->z + add.z);
	}

	vec3 operator-(const vec3 sub)
	{
		return vec3(this->x - sub.x, this->y - sub.y, this->z - sub.z);
	}	
};

struct vec2
{
	float x, y;

	vec2()
	{
		x = 0;
		y = 0;
	}

	vec2(float val)
	{
		x = val;
		y = val;
	}

	vec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	vec2 operator-(const vec2 &right)
	{
		return vec2(this->x - right.x, this->y - right.y);
	}	

	vec2 operator*(const vec2 &right)
	{
		return vec2(this->x * right.x, this->y * right.y);
	}
};

struct Vertex
{
	vec3 position;
	vec2 tex_coords;
	vec4 color;

	bool valid;

	Vertex()
	{
		position = vec3();
		tex_coords = vec2();
		color = vec4();

		valid = false;
	}	

	Vertex(vec3 _position)
	{
		position = _position;

		valid = true;
	}

	Vertex(vec3 _position, vec2 _tex_coords, vec4 _color)
	{
		position = _position;
		tex_coords = _tex_coords;
		color = _color;

		valid = true;
	}
};

struct transform
{
	vec3 position;
	vec3 scale;
	vec3 rotation;

	vec3 origin;

	transform()
	{
		position = vec3(0.0f);
		scale = vec3(1.0f);
		rotation = vec3(0.0f);

		origin = vec3(0.0f);
	}

	bool operator==(const transform &other)
	{
		return 
			this->position.x == other.position.x &&
			this->position.y == other.position.y &&
			this->position.z == other.position.z &&
			this->rotation.x == other.rotation.x &&
			this->rotation.y == other.rotation.y &&
			this->rotation.z == other.rotation.z &&
			this->scale.x == other.scale.x &&
			this->scale.y == other.scale.y &&
			this->scale.z == other.scale.z;
	}

	bool operator!=(const transform &other)
	{
		return !(*this == other);
	}

	vec3 forward();

	vec3 right();

	vec3 up();

	mat4x4 matrix();	
};

mat4x4 get_identity();

mat4x4 get_perspective(float width, float height, float z_near, float z_far, float fov);

mat4x4 get_rotation_x(float degrees);

mat4x4 get_rotation_y(float degrees);

mat4x4 get_rotation_z(float degrees);

mat4x4 get_rotation(vec3 rotation);

mat4x4 get_scale(vec3 scale);

mat4x4 get_translation(vec3 translate);

mat4x4 mat4_transpose_translate(mat4x4 matrix);

mat4x4 mat4_transpose(mat4x4 matrix);

float rad_to_deg(float radians);

float deg_to_rad(float degrees);

vec3 vec4_to_vec3(vec4 vec);

vec4 vec3_to_vec4(vec3 vec);
