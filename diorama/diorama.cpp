#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"
#include "entity.h"
#include "drawing.h"
#include "input.h"

#include <stdio.h>

#include <vector>
#include <algorithm>

std::vector<entity*> entities;

vec3 camera_orbit;

transform default_camera;
transform transform_camera;
transform transform_camera_prev;

bool rotating_y;
float start_rotating_time;
float start_rotating_y;
float desired_rotating_y;

static float timescale = 1.0f;

const static int MAX_TILES_X = 10;
const static int MAX_TILES_Y = 10;
const static int MAX_TILES_Z = 10;

cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z];

keybind_event *kb_event;

void diorama_init()
{
	kb_event = keybind_subscribe(diorama_keybind_updated);

	camera_orbit = vec3(0.0f, -8.0f, -8.0f);
	default_camera = transform();
	default_camera.position = vec3(-1.5f, -8.0f - 3.0f, -8.0f - 1.5f);
	default_camera.rotation = vec3(45.0f, 0.0f, 0.0f);
	default_camera.scale = vec3(1.0f, 1.0f, 1.0f);

	transform_camera = default_camera;
	
	transform_camera_prev = transform_camera;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				cube *c = new cube();
				create_entity(c, transform(vec3(x, y, z), vec3(0.0f), vec3(1.0f)));

				tiles[x][y][z] = c;
			}
		}
	}
}

void diorama_update()
{
	float time = (float)glfwGetTime();

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->update(time);
	}

	if (rotating_y)
	{
		float period = 0.25f;

		float percent = (time - start_rotating_time) / period;

		transform_camera.rotation.y = lerp(start_rotating_y, desired_rotating_y, percent);

		if (percent > 0.99f)
		{
			transform_camera.rotation.y = desired_rotating_y;
			rotating_y = false;
		}
	}
}

void diorama_keybind_updated(keybind bind)
{
	vec3 forward = transform_camera.forward();
	vec3 right = transform_camera.right();

	if ((bind.state == INPUT_HOLD || bind.state == INPUT_PRESS) && bind.name == "forward")
		transform_camera.position = transform_camera.position - forward * 0.1f;	
	if ((bind.state == INPUT_HOLD || bind.state == INPUT_PRESS) && bind.name == "backward")
		transform_camera.position = transform_camera.position + forward * 0.1f;
	if ((bind.state == INPUT_HOLD || bind.state == INPUT_PRESS) && bind.name == "left")
		transform_camera.position = transform_camera.position + right * 0.1f;
	if ((bind.state == INPUT_HOLD || bind.state == INPUT_PRESS) && bind.name == "right")		
		transform_camera.position = transform_camera.position - right * 0.1f;

	if (bind.name == "rotate_cw" && bind.state == INPUT_PRESS && !rotating_y)
	{
		rotating_y = true;
		start_rotating_y = transform_camera.rotation.y;
		desired_rotating_y = transform_camera.rotation.y + 45.0f;
		start_rotating_time = (float)glfwGetTime();		
	}

	if (bind.name == "rotate_ccw" && bind.state == INPUT_PRESS && !rotating_y)
	{
		rotating_y = true;
		start_rotating_y = transform_camera.rotation.y;
		desired_rotating_y = transform_camera.rotation.y - 45.0f;
		start_rotating_time = (float)glfwGetTime();		
	}
}

void diorama_draw()
{
	clear_glerrors();

	GLFWwindow *window = glfwGetCurrentContext();

	int width, height;
	float ratio;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	draw_world(width, height, ratio);

	glfwSwapBuffers(window);
}

void draw_world(int width, int height, float ratio)
{
	glUseProgram(program_general);

	float pers_near = 1.0f;
	float pers_far = 1000.0f;

	float top, bottom, left, right;
	compute_screen_coordinates(45, (float)width / (float)height, pers_near, pers_far, left, right, top, bottom);
	mat4x4 matrix = get_perspective(left, right, top, bottom, pers_near, pers_far);

	mat4x4 camera = get_rotation_x(transform_camera.rotation.x) * 
		get_translation(camera_orbit) * 
		get_rotation_y(transform_camera.rotation.y * -1) * 
		get_translation(transform_camera.position + camera_orbit * -1);

	uniform_mat4(program_general, "projection", 1, true, matrix.m); 
	uniform_mat4(program_general, "camera", 1, true, camera.m); 

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	
	glEnable(GL_MULTISAMPLE);

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->draw();
	}

	printf_glerrors();	
}

int create_entity(entity *ent, transform trans)
{
	entities.push_back(ent);

	ent->init(trans);

	return entities.size() - 1;
}

void sort_entities()
{
	std::sort(entities.begin(), entities.end(), get_sort_entities);		
}

bool get_sort_entities(const entity *i, const entity *j)
{
	vec3 i_dist_to_cam = (transform_camera.position - i->trans.position);
	vec3 j_dist_to_cam = (transform_camera.position - j->trans.position);

	return i_dist_to_cam.length() < j_dist_to_cam.length(); 
}
