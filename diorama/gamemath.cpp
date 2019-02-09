#include "gamemath.h"

#include <math.h>

mat4x4 * get_identity()
{
	mat4x4 * matrix = new mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
					   	   0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f);

	return matrix;	
}

mat4x4 * get_perspective(float width, float height, float z_near, float z_far, float fov)
{
	const float ar = width / height;
	const float z_range = z_near - z_far;
	const float half_fov = (float)tan(deg_to_rad(fov / 2.0f));

	mat4x4 * matrix = new mat4x4();

	matrix->m[0] = 1.0f / (half_fov * ar);
	matrix->m[1] = 0.0f;
	matrix->m[2] = 0.0f;
	matrix->m[3] = 0.0f;

	matrix->m[4] = 0.0f;
	matrix->m[5] = 1.0f / half_fov;
	matrix->m[6] = 0.0f;
	matrix->m[7] = 0.0f;

	matrix->m[8] = 0.0f;
	matrix->m[9] = 0.0f;
	matrix->m[10] = (-z_near - z_far) / z_range;
	matrix->m[11] = 2.0f * z_far * z_near / z_range;

	matrix->m[12] = 0.0f;
	matrix->m[13] = 0.0f;
	matrix->m[14] = 1.0f;
	matrix->m[15] = 0.0f;		
	
	return matrix;
}

vec3 mat4x4_vec3_mult(vec3 vector, mat4x4 matrix)
{
	vec3 f = vec3(0.0f, 0.0f, 0.0f);

	f.x = matrix.m[0] * vector.x + matrix.m[1] * vector.y + matrix.m[2] * vector.z + matrix.m[3] * 1;
	f.y = matrix.m[4] * vector.x + matrix.m[5] * vector.y + matrix.m[6] * vector.z + matrix.m[7] * 1;
	f.z = matrix.m[8] * vector.x + matrix.m[9] * vector.y + matrix.m[10] * vector.z + matrix.m[11] * 1;
	//NOOP for last point since we don't need it

	return f;
}

float rad_to_deg(float radians)
{
	return radians * 57.2958f;
}

float deg_to_rad(float degrees)
{
	return degrees * 0.0174533f;
}
