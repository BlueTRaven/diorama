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

void diorama_init();

void diorama_draw();
void draw_world(int width, int height, float ratio);

void diorama_keybind_updated(keybind bind);

void diorama_update();

int create_entity(entity *ent, transform trans);

void sort_entities();
bool get_sort_entities(const entity *i, const entity *j);
