#pragma once

#include "vertex_handler.h"

#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern std::vector<vertex_array*> vertex_arrays;

void draw(GLint program);

void update_input();

void update();
