#pragma once

#include "vertex_handler.h"

#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern std::vector<vertex_array*> vertex_arrays;

extern GLint program_general;

void draw();
void draw_world(int width, int height, float ratio);

void update_input();

void update();
