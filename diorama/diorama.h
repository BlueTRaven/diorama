#pragma once

#include "gamemath.h"
#include "vertex_handler.h"
#include "entity.h"
#include "input.h"

#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern std::vector<vertex_array*> vertex_arrays;

extern GLint program_general;

extern transform camera_transform;

void diorama_init();

void diorama_draw();
void draw_world(int width, int height, float ratio);

void diorama_keybind_updated(keybind bind);
void diorama_player_keybind_updated(keybind bind);

void diorama_update();

void set_selected_tile(vec3 position);
bool is_valid_tile(vec3 position);

int create_entity(entity *ent, transform trans);

void create_cube(entity *ent, cube *c);

void create_player(entity *ent, player *_pl);
