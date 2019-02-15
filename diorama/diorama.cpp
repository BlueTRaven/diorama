#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"
#include "entity.h"
#include "drawing.h"

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

int keystate_w;
int keystate_a;
int keystate_s;
int keystate_d;

int keystate_q;
int keystate_e;

int keystate_z;
int keystate_x;

const int INPUT_PRESS = 1;
const int INPUT_HOLD = 2;
const int INPUT_RELEASE = 3;
const int INPUT_NONE = 0;

static float timescale = 1.0f;

const static int MAX_TILES_X = 10;
const static int MAX_TILES_Y = 10;
const static int MAX_TILES_Z = 10;

cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z];

void diorama_init()
{
	//camera_orbit = vec3(0.0f);
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

void diorama_update_input()
{
	glfwPollEvents();

	vec3 forward = transform_camera.forward();
	vec3 right = transform_camera.right();

	if (keystate_w == INPUT_HOLD)
		transform_camera.position = transform_camera.position - forward * 0.1f;
	if (keystate_a == INPUT_HOLD)
		transform_camera.position = transform_camera.position + right * 0.1f;
	if (keystate_s == INPUT_HOLD)
		transform_camera.position = transform_camera.position + forward * 0.1f;
	if (keystate_d == INPUT_HOLD)
		transform_camera.position = transform_camera.position - right * 0.1f;

	if (keystate_z == INPUT_HOLD)
		transform_camera.position.y += 0.1f;
	if (keystate_x == INPUT_HOLD)
		transform_camera.position.y -= 0.1f;

	if (keystate_w == INPUT_PRESS)
		keystate_w = INPUT_HOLD;
	if (keystate_a == INPUT_PRESS)
		keystate_a = INPUT_HOLD;
	if (keystate_s == INPUT_PRESS)
		keystate_s = INPUT_HOLD;
	if (keystate_d == INPUT_PRESS)
		keystate_d = INPUT_HOLD;

	if (keystate_q == INPUT_PRESS && !rotating_y)
	{
		keystate_q = INPUT_HOLD;

		rotating_y = true;
		start_rotating_y = transform_camera.rotation.y;
		desired_rotating_y = transform_camera.rotation.y + 45.0f;
		start_rotating_time = (float)glfwGetTime();
	}
	if (keystate_e == INPUT_PRESS && !rotating_y)
	{
		keystate_e = INPUT_HOLD;

		rotating_y = true;
		start_rotating_y = transform_camera.rotation.y;
		desired_rotating_y = transform_camera.rotation.y - 45.0f;
		start_rotating_time = (float)glfwGetTime();
	}

	if (keystate_z == INPUT_PRESS)
		keystate_z = INPUT_HOLD;
	if (keystate_x == INPUT_PRESS)
		keystate_x = INPUT_HOLD;
	
	if (keystate_w == INPUT_RELEASE)
		keystate_w = INPUT_NONE;
	if (keystate_a == INPUT_RELEASE)
		keystate_a = INPUT_NONE;
	if (keystate_s == INPUT_RELEASE)
		keystate_s = INPUT_NONE;
	if (keystate_d == INPUT_RELEASE)
		keystate_d = INPUT_NONE;

	if (keystate_q == INPUT_RELEASE)
		keystate_q = INPUT_NONE;
	if (keystate_e == INPUT_RELEASE)
		keystate_e = INPUT_NONE;

	if (keystate_z == INPUT_RELEASE)
		keystate_z = INPUT_NONE;
	if (keystate_x == INPUT_RELEASE)
		keystate_x = INPUT_NONE;
}

void diorama_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
		check_keystate(keystate_w, action);	
	if (key == GLFW_KEY_A)
		check_keystate(keystate_a, action);	
	if (key == GLFW_KEY_S)
		check_keystate(keystate_s, action);	
	if (key == GLFW_KEY_D)
		check_keystate(keystate_d, action);	

	if (key == GLFW_KEY_Q)
		check_keystate(keystate_q, action);	
	if (key == GLFW_KEY_E)
		check_keystate(keystate_e, action);	

	if (key == GLFW_KEY_Z)
		check_keystate(keystate_z, action);
	if (key == GLFW_KEY_X)
		check_keystate(keystate_x, action);

	if (key == GLFW_KEY_R)
	{
		transform_camera = default_camera;
	}
}

void check_keystate(int &keystate, int action)
{
	if (action == GLFW_PRESS)
		keystate = INPUT_PRESS;
	else if (action == GLFW_RELEASE)
		keystate = INPUT_RELEASE;
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
