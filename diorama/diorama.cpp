#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"
#include "entity.h"

#include <stdio.h>
using namespace std;

vector<entity*> entities;

transform *transform_camera;

int keystate_w;
int keystate_a;
int keystate_s;
int keystate_d;

int keystate_q;
int keystate_e;

const int INPUT_PRESS = 1;
const int INPUT_RELEASE = 2;
const int INPUT_NONE = 0;

void diorama_init()
{
	entities.push_back(new cube());

	transform_camera = new transform();
	transform_camera->position = vec3(0.0f, 0.0f, 0.0f);
	transform_camera->rotation = vec3(0.0f, 0.0f, 0.0f);
	transform_camera->scale = vec3(1.0f, 1.0f, 1.0f);

	init_entities();
}

void init_entities()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->init();
	}
}

void update()
{
	double time = glfwGetTime();

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->update();
	}
}

void update_input()
{
	glfwPollEvents();

	if (keystate_w == INPUT_PRESS)
		transform_camera->position = transform_camera->position + transform_camera->forward() * 0.1f;
	if (keystate_a == INPUT_PRESS)
		transform_camera->position = transform_camera->position + transform_camera->right() * 0.1f;
	if (keystate_s == INPUT_PRESS)
		transform_camera->position = transform_camera->position - transform_camera->forward() * 0.1f;
	if (keystate_d == INPUT_PRESS)
		transform_camera->position = transform_camera->position - transform_camera->right() * 0.1f;

	if (keystate_q == INPUT_PRESS)
		transform_camera->rotation.y += 1.0f;
	if (keystate_e == INPUT_PRESS)
		transform_camera->rotation.y -= 1.0f;

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

	if (key == GLFW_KEY_R)
	{
		transform_camera = new transform();
		transform_camera->position = vec3(0.0f, 0.0f, 0.0f);
		transform_camera->scale = vec3(1.0f, 1.0f, 1.0f);
		transform_camera->rotation = vec3(0.0f, 0.0f, 0.0f);
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
	GLFWwindow *window = glfwGetCurrentContext();

	int width, height;
	float ratio;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw_world(width, height, ratio);

	glfwSwapBuffers(window);
}

void draw_world(int width, int height, float ratio)
{
	glUseProgram(program_general);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_arrays[0]->vert_buffer);

	GLint attrib_position = vertex_attribute(program_general, "position", 3, sizeof(Vertex), (void*)0);
	GLint attrib_tex_coord = vertex_attribute(program_general, "tex_coord", 2, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	GLint attrib_color = vertex_attribute(program_general, "color", 4, sizeof(Vertex), (void*)offsetof(Vertex, color));

	mat4x4 matrix = get_perspective(width, height, 1.0f, 10000.0f, 45.0f);

 	mat4x4 camera = get_translation(transform_camera->position) * get_rotation(transform_camera->rotation) ;

	uniform_mat4(program_general, "projection", 1, false, matrix.m); 
	uniform_mat4(program_general, "camera", 1, true, camera.m); 

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->draw();
	}

	disable_vertex_attribute(attrib_position);
	disable_vertex_attribute(attrib_tex_coord);
	disable_vertex_attribute(attrib_color);
}
