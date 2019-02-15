#include "gamemath.h"
#include "camera.h"
#include "entity.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

vec3 camera_orbit;

transform camera_transform;
transform camera_default;
transform camera_transform_previous;

bool rotating_y;
float start_rotating_time;
float start_rotating_y;
float desired_rotating_y;

void camera_init(transform cam_start)
{
	camera_orbit = vec3(0.0f, -8.0f, -8.0f);

	camera_transform = cam_start;
	camera_default = cam_start;
	camera_transform_previous = cam_start;
}

void camera_update(float time)
{
	if (rotating_y)
	{
		float period = 0.25f;

		float percent = (time - start_rotating_time) / period;

		camera_transform.rotation.y = lerp(start_rotating_y, desired_rotating_y, percent);

		if (percent > 0.99f)
		{
			camera_transform.rotation.y = desired_rotating_y;
			rotating_y = false;
		}
	}
}

void camera_start_rotating(int direction)
{
	if (!rotating_y)
	{
		rotating_y = true;
		start_rotating_y = camera_transform.rotation.y;
		desired_rotating_y = camera_transform.rotation.y + (45.0f * direction);
		start_rotating_time = (float)glfwGetTime();		
	}
}

mat4x4 camera_get_matrix()
{
	return get_rotation_x(camera_transform.rotation.x) * 
		get_translation(camera_orbit) * 
		get_rotation_y(camera_transform.rotation.y * -1) * 
		get_translation(camera_transform.position + camera_orbit * -1);
}

void camera_follow_entity(entity *entity)
{
	camera_transform.position = (entity->trans.position * -1) + camera_orbit - vec3(0.5f); 
}
