#pragma once

#include "vertex_handler.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern GLuint vertex_buffer;
extern GLuint vertex_array;

void draw(GLint program);

void update_input();

void update();
