#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"
#include "entity.h"
#include "drawing.h"
#include "input.h"
#include "camera.h"

#include <stdio.h>

#include <vector>
#include <algorithm>

std::vector<entity*> entities;

static float timescale = 1.0f;

const static int MAX_TILES_X = 10;
const static int MAX_TILES_Y = 10;
const static int MAX_TILES_Z = 10;

cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z];

cube *selected;

keybind_event *kb_event;

void diorama_init()
{
	kb_event = keybind_subscribe(diorama_keybind_updated);

	transform default_camera = transform();
	default_camera.position = vec3(-1.5f, -8.0f - 3.0f, -8.0f - 1.5f);
	default_camera.rotation = vec3(45.0f, 0.0f, 0.0f);
	default_camera.scale = vec3(1.0f, 1.0f, 1.0f);

	camera_init(default_camera);

	create_entity(new player(), transform(vec3(1.0f, 3.0f, 1.0f), vec3(0.0f), vec3(1.0f)));

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				tiles[x][y][z] = NULL; //init all tiles to null
			}
		}
	}

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

	set_selected_tile(vec3(1.0f, 2.0f, 1.0f));	
}

void diorama_update()
{
	float time = (float)glfwGetTime();

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->update(time);
	}

	camera_update(time);
}

bool is_valid_tile(vec3 position)
{
	if (position.x < 0 || position.y < 0 || position.z < 0)
		return false;
	if (position.x >= MAX_TILES_X || position.y >= MAX_TILES_Y || position.z >= MAX_TILES_Z)
		return false;

	return tiles[(int)position.x][(int)position.y][(int)position.z] != NULL;
}

void set_selected_tile(vec3 position)
{
	if (is_valid_tile(position))
	{
		if (selected != NULL)
			selected->flags = selected->flags & ~selected->SELECTED;
		selected = tiles[(int)position.x][(int)position.y][(int)position.z];
		selected->flags |= selected->SELECTED;

		camera_follow_entity(selected);
	}
}

void diorama_keybind_updated(keybind bind)
{
	vec3 forward = camera_transform.forward();
	vec3 right = camera_transform.right();

	if ((bind.state == INPUT_PRESS) && bind.name == "forward")
		set_selected_tile(selected->trans.position + vec3(0.0f, 0.0f, -1.0f));
	if ((bind.state == INPUT_PRESS) && bind.name == "backward")
		set_selected_tile(selected->trans.position + vec3(0.0f, 0.0f, 1.0f));
	if ((bind.state == INPUT_PRESS) && bind.name == "left")
		set_selected_tile(selected->trans.position + vec3(-1.0f, 0.0f, 0.0f));
	if ((bind.state == INPUT_PRESS) && bind.name == "right")		
		set_selected_tile(selected->trans.position + vec3(1.0f, 0.0f, 0.0f));

	if (bind.name == "rotate_cw" && bind.state == INPUT_PRESS)
		camera_start_rotating(-1);

	if (bind.name == "rotate_ccw" && bind.state == INPUT_PRESS)
		camera_start_rotating(1);
}

void diorama_draw()
{
	clear_glerrors();

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

	float pers_near = 1.0f;
	float pers_far = 1000.0f;

	float top, bottom, left, right;
	compute_screen_coordinates(45, (float)width / (float)height, pers_near, pers_far, left, right, top, bottom);
	mat4x4 matrix = get_perspective(left, right, top, bottom, pers_near, pers_far);

	uniform_mat4(program_general, "projection", 1, true, matrix.m); 
	uniform_mat4(program_general, "camera", 1, true, camera_get_matrix().m); 

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
