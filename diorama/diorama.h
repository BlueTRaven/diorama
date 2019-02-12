#pragma once

#include "gamemath.h"
#include "vertex_handler.h"
#include "entity.h"

#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern std::vector<vertex_array*> vertex_arrays;

extern GLint program_general;

void diorama_init();

void draw();
void draw_world(int width, int height, float ratio);

void update_input();
void diorama_key(GLFWwindow *window, int key, int scancode, int action, int mods);

void check_keystate(int &keystate, int action);

void update();

int create_entity(entity *ent, transform *trans);
