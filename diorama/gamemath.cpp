#include "gamemath.h"

#include <math.h>

mat4x4 get_identity()
{
	mat4x4 matrix = mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
					   	   0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f);

	return matrix;	
}

mat4x4 get_perspective(float width, float height, float z_near, float z_far, float fov)
{
	const float ar = width / height;
	const float z_range = z_far - z_near;
	const float half_fov = (float)tan(deg_to_rad(fov / 2.0f));

	mat4x4 matrix = mat4x4();

	matrix.m[0] = 1.0f / (half_fov * ar);
	matrix.m[1] = 0.0f;
	matrix.m[2] = 0.0f;
	matrix.m[3] = 0.0f;

	matrix.m[4] = 0.0f;
	matrix.m[5] = 1.0f / half_fov;
	matrix.m[6] = 0.0f;
	matrix.m[7] = 0.0f;

	matrix.m[8] = 0.0f;
	matrix.m[9] = 0.0f;
	matrix.m[10] = (-z_near - z_far) / z_range;
	matrix.m[11] = 2.0f * z_far * z_near / z_range;

	matrix.m[12] = 0.0f;
	matrix.m[13] = 0.0f;
	matrix.m[14] = -1.0f;
	matrix.m[15] = 0.0f;		
	
	return matrix;
}

void compute_screen_coordinates(const float &angle_of_view, const float &aspect_ratio, const float &pers_near, const float &pers_far, float &left, float &right, float &top, float &bottom) 
{
	float scale = tan(angle_of_view * 0.5f * 3.1415f / 180) * pers_near;
	right = aspect_ratio * scale, left = -right;
	top = scale, bottom = -top;
}

mat4x4 get_perspective_2(float left, float right, float top, float bottom, float pers_near, float pers_far)
{
	mat4x4 matrix = mat4x4();

	//row 1
	matrix.m[0] = (2 * pers_near) / (right - left);
	matrix.m[1] = 0;
	matrix.m[2] = (right + left) / (right - left);
	matrix.m[3] = 0;

	//row 2
	matrix.m[4] = 0;
	matrix.m[5] = (2 * pers_near) / (top - bottom);
	matrix.m[6] = (top + bottom) / (top - bottom);
	matrix.m[7] = 0;

	//row 3	
	matrix.m[8] = 0;
	matrix.m[9] = 0;
	matrix.m[10] = -((pers_far + pers_near) / (pers_far - pers_near));
	matrix.m[11] = -((2 * pers_far * pers_near) / (pers_far - pers_near));

	//row 4	
	matrix.m[12] = 0;
	matrix.m[13] = 0;
	matrix.m[14] = -1;
	matrix.m[15] = 0;

	return matrix;
}

mat4x4 get_rotation_x(float degrees)
{
	float radians = deg_to_rad(degrees);

	float sinf = (float)sin(radians);
	float cosf = (float)cos(radians);
	
	mat4x4 matrix = mat4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosf, -sinf, 0.0f,
			0.0f, sinf, cosf, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	return matrix;
}

mat4x4 get_rotation_y(float degrees)
{
	float radians = deg_to_rad(degrees);

	float sinf = (float)sin(radians);
	float cosf = (float)cos(radians);

	mat4x4 matrix = mat4x4(
			cosf, 0.0f, sinf, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-sinf, 0.0f, cosf, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	return matrix;
}

mat4x4 get_rotation_z(float degrees)
{
	float radians = deg_to_rad(degrees);

	float sinf = (float)sin(radians);
	float cosf = (float)cos(radians);

	mat4x4 matrix = mat4x4(
			cosf, -sinf, 0.0f, 0.0f,
			sinf, cosf, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	return matrix;
}

mat4x4 get_rotation(vec3 rotation)
{
	mat4x4 x = get_rotation_x(rotation.x);
	mat4x4 y = get_rotation_y(rotation.y);
	mat4x4 z = get_rotation_z(rotation.z);

	return x * y * z;
}

mat4x4 get_scale(vec3 scale)
{
	mat4x4 matrix = mat4x4(
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	return matrix;
}

mat4x4 get_translation(vec3 translate)
{
	mat4x4 matrix = mat4x4(
			1.0f, 0.0f, 0.0f, translate.x,
			0.0f, 1.0f, 0.0f, translate.y,
			0.0f, 0.0f, 1.0f, translate.z,
			0.0f, 0.0f, 0.0f, 1.0f);

	return matrix;
}

mat4x4 mat4_transpose(mat4x4 matrix)
{
	mat4x4 out = mat4x4();

	out.m[4] = matrix[1];
	out.m[1] = matrix[4];

	out.m[8] = matrix[2];
	out.m[2] = matrix[8];

	out.m[12] = matrix[3];
	out.m[3] = matrix[12];

	out.m[9] = matrix[6];
	out.m[6] = matrix[9];

	out.m[13] = matrix[7];
	out.m[7] = matrix[13];

	out.m[14] = matrix[11];
	out.m[11] = matrix[14];

	out.m[0] = matrix[0];
	out.m[5] = matrix[5];
	out.m[10] = matrix[10];
	out.m[15] = matrix[15];

	return out;
}

mat4x4 mat4x4::inverse()
{
	return mat4x4(
			this->m[0] * -1, this->m[1] * -1, this->m[2] * -1, this->m[3] * -1,
			this->m[4] * -1, this->m[5] * -1, this->m[6] * -1, this->m[7] * -1,
			this->m[8] * -1, this->m[9] * -1, this->m[10] * -1, this->m[11] * -1,
			this->m[12] * -1, this->m[13] * -1, this->m[14] * -1, this->m[15] * -1);
}

float rad_to_deg(float radians)
{
	return radians * 57.2958f;
}

float deg_to_rad(float degrees)
{
	return degrees * 0.0174533f;
}

vec3 vec4_to_vec3(vec4 vec)
{
	return vec3(vec.x, vec.y, vec.z);
}

vec4 vec3_to_vec4(vec3 vec, float w)
{
	return vec4(vec.x, vec.y, vec.z, w);
}

float vec3::length()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

vec3 vec3::normalized()
{
	float len = this->length();
	return vec3(this->x / len, this->y / len, this->z / len);
}

mat4x4 transform::matrix()
{
	mat4x4 scale = get_scale(this->scale);
	mat4x4 rotate = get_translation(this->origin * (this->scale * -1)) * 
		get_rotation(this->rotation) * 
		get_translation(this->origin * this->scale);
	mat4x4 translate = get_translation(this->position);

	return (rotate * scale) * translate; 
}

vec3 transform::forward()
{
	mat4x4 rotation = get_rotation_y(this->rotation.y);
	vec4 forward = rotation * vec4(0.0f, 0.0f, -1.0f, 1.0f);
	return vec4_to_vec3(forward).normalized();
}

vec3 transform::right()
{
	mat4x4 rotation = mat4_transpose(get_rotation_y(this->rotation.y));
	return (vec3(1.0f, 0.0f, 0.0f) * rotation).normalized();
}

vec3 transform::up()
{
	mat4x4 rotation = get_rotation_y(this->rotation.x);
	return (vec3(0.0f, 1.0f, 0.0f) * rotation).normalized();
}
