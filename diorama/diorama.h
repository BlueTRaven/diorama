#pragma once

#include "vertex_handler.h"

#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern std::vector<vertex_array*> vertex_arrays;

extern GLint program_general;

static bool draw_wireframe;

void diorama_init();

void init_entities();

void draw();
void draw_world(int width, int height, float ratio);

void update_input();
void diorama_key(GLFWwindow *window, int key, int scancode, int action, int mods);

void check_keystate(int &keystate, int action);

void update();
