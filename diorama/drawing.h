#pragma once

#include "vertex_handler.h"
#include "gamemath.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern GLint program_general;
extern bool draw_wireframe;

void draw_vertdata(vertex_data *data, transform *trans);