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
#include "game.h"
#include "shader.h"

#include <stdio.h>

#include <vector>
#include <algorithm>

static float timescale = 1.0f;

std::vector<entity*> entities;

cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z];
cube *editor_tile_selected;

player *pl;

keybind_event *kb_event;
keybind_event *player_kb_event;

void diorama_init(std::map<std::string, Decl> cube_types)
{
	diorama_state = DIORAMA_STATE_GAME;

	kb_event = keybind_subscribe(diorama_keybind_updated);
	player_kb_event = keybind_subscribe(diorama_player_keybind_updated);

	transform default_camera = transform();
	default_camera.position = vec3(-1.5f, -8.0f - 3.0f, -8.0f - 1.5f);
	default_camera.rotation = vec3(45.0f, 0.0f, 0.0f);
	default_camera.scale = vec3(1.0f, 1.0f, 1.0f);

	camera_init(default_camera);

	entity *ent = new entity();
	player *pl = new player();

	create_entity(ent, transform(vec3(1.0f, 3.0f, 1.0f), vec3(0.0f), vec3(1.0f)));
	create_player(ent, pl);

	for (int x = 0; x < MAX_TILES_X; x++)
	{
		for (int y = 0; y < MAX_TILES_Y; y++)
		{
			for (int z = 0; z < MAX_TILES_Z; z++)
			{	//init all tiles to air.
				ent = new entity();
				create_entity(ent, transform(vec3(x, y, z), vec3(0.0f), vec3(1.0f)));
				
				cube *c = new cube();
				create_cube(ent, c, cube_types["air"]);
			}
		}
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				ent = new entity();
				create_entity(ent, transform(vec3(x, y, z), vec3(0.0f), vec3(1.0f)));
				
				cube *c = new cube();
				create_cube(ent, c, cube_types["grass_01"]);
			}
		}
	}

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = 0; z < 5; z++)
			{
				ent = new entity();
				create_entity(ent, transform(vec3(x, y, z), vec3(0.0f), vec3(1.0f)));
				
				cube *c = new cube();
				create_cube(ent, c, cube_types["grass_01"]);
			}
		}
	}	

	if (diorama_state == DIORAMA_STATE_EDITOR)
		set_selected_tile(vec3(1.0f, 2.0f, 1.0f));	
}

void diorama_update()
{
	float time = (float)glfwGetTime();

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				if (is_valid_tile(vec3(x, y, z)))
					cube_update(tiles[x][y][z], time);
			}
		}
	}

	player_update(pl, time);

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
		if (editor_tile_selected != NULL)
			editor_tile_selected->ent->flags = editor_tile_selected->ent->flags & ~CUBE_SELECTED;
		editor_tile_selected = tiles[(int)position.x][(int)position.y][(int)position.z];
		editor_tile_selected->ent->flags |= CUBE_SELECTED;

		camera_follow_entity(editor_tile_selected->ent);
	}
}

void diorama_keybind_updated(keybind bind)
{
	vec3 forward = camera_transform.forward();
	vec3 right = camera_transform.right();

	if (diorama_state == DIORAMA_STATE_EDITOR)
	{
		if ((bind.state == INPUT_PRESS) && bind.name == "forward")
			set_selected_tile(editor_tile_selected->ent->trans.position + vec3(0.0f, 0.0f, -1.0f));
		if ((bind.state == INPUT_PRESS) && bind.name == "backward")
			set_selected_tile(editor_tile_selected->ent->trans.position + vec3(0.0f, 0.0f, 1.0f));
		if ((bind.state == INPUT_PRESS) && bind.name == "left")
			set_selected_tile(editor_tile_selected->ent->trans.position + vec3(-1.0f, 0.0f, 0.0f));
		if ((bind.state == INPUT_PRESS) && bind.name == "right")		
			set_selected_tile(editor_tile_selected->ent->trans.position + vec3(1.0f, 0.0f, 0.0f));
	}

	if (bind.name == "rotate_cw" && bind.state == INPUT_PRESS)
		camera_start_rotating(-1);

	if (bind.name == "rotate_ccw" && bind.state == INPUT_PRESS)
		camera_start_rotating(1);
}

void diorama_player_keybind_updated(keybind bind)
{
	player_keybind_updated(pl, (float)glfwGetTime(), tiles, bind);
}

void diorama_draw()
{
	glerrors_startlisten();

	GLFWwindow *window = glfwGetCurrentContext();

	int width, height;
	float ratio;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	draw_world(width, height, ratio);

	glfwSwapBuffers(window);
}

void draw_world(int width, int height, float ratio)
{
	/*glerrors_startlisten();	
	glUseProgram(shaders["generic"].program);
	glerrors_endlisten("Using Program");

	float pers_near = 1.0f;
	float pers_far = 1000.0f;

	float top, bottom, left, right;
	compute_screen_coordinates(45, (float)width / (float)height, pers_near, pers_far, left, right, top, bottom);
	mat4x4 matrix = get_perspective(left, right, top, bottom, pers_near, pers_far);

	uniform_mat4(program_general, "projection", 1, true, matrix.m); 
	uniform_mat4(program_general, "camera", 1, true, camera_get_matrix().m); */

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	
	glEnable(GL_MULTISAMPLE);

	glerrors_startlisten();
	
	for (int i = 0; i < entities.size(); i++)
		entity_draw(entities[i]);

	glerrors_endlisten("Draw Entities");

	glerrors_endlisten("Draw World");	
}

int create_entity(entity *ent, transform trans)
{
	entities.push_back(ent);

	entity_init(ent, trans);

	return entities.size() - 1;
}

void create_cube(entity *ent, cube *c, Decl cube_asset)
{
	if (is_valid_tile(ent->trans.position))
		delete tiles[(int)ent->trans.position.x][(int)ent->trans.position.y][(int)ent->trans.position.z]; 

	tiles[(int)ent->trans.position.x][(int)ent->trans.position.y][(int)ent->trans.position.z] = c;
	cube_init(ent, c, cube_asset);
}

void create_player(entity *ent, player *_pl)
{
	pl = _pl;
	player_init(ent, pl);
}
