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

transform default_camera;

transform transform_camera;
transform transform_camera_prev;

int keystate_w;
int keystate_a;
int keystate_s;
int keystate_d;

int keystate_q;
int keystate_e;

int keystate_z;
int keystate_x;

const int INPUT_PRESS = 1;
const int INPUT_RELEASE = 2;
const int INPUT_NONE = 0;

static float timescale = 1.0f;

const static int MAX_TILES_X = 10;
const static int MAX_TILES_Y = 10;
const static int MAX_TILES_Z = 10;

cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z];

void diorama_init()
{
	default_camera = transform();
	default_camera.position = vec3(0.0f);//vec3(0.0f, -5.0f, -5.0f);
	default_camera.rotation = vec3(0.0f);//vec3(45.0f, 0.0f, 0.0f);
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

void update()
{
	float time = (float)glfwGetTime();

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->update(time);
	}
}

void update_input()
{
	glfwPollEvents();

	vec3 forward = transform_camera.forward();
	vec3 right = transform_camera.right();

	if (keystate_w == INPUT_PRESS)
		transform_camera.position = transform_camera.position - forward * 0.1f;
	if (keystate_a == INPUT_PRESS)
		transform_camera.position = transform_camera.position + right * 0.1f;
	if (keystate_s == INPUT_PRESS)
		transform_camera.position = transform_camera.position + forward * 0.1f;
	if (keystate_d == INPUT_PRESS)
		transform_camera.position = transform_camera.position - right * 0.1f;

	if (keystate_q == INPUT_PRESS)
		transform_camera.rotation.y += 1.0f;
	if (keystate_e == INPUT_PRESS)
		transform_camera.rotation.y -= 1.0f;

	if (keystate_z == INPUT_PRESS)
		transform_camera.position.y += 0.1f;
	if (keystate_x == INPUT_PRESS)
		transform_camera.position.y -= 0.1f;

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
	
void draw()
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

	mat4x4 matrix = get_perspective(width, height, 1.0f, 100.0f, 60.0f);

 	mat4x4 camera = get_rotation(transform_camera.rotation) * get_translation(transform_camera.position);

	uniform_mat4(program_general, "projection", 1, true, matrix.m); 
	uniform_mat4(program_general, "camera", 1, true, camera.m); 

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	
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
