#pragma once

#include "vertex_handler.h"
#include "gamemath.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

extern GLint program_general;
extern bool draw_wireframe;

void draw_vertdata(vertex_array *vert_array, transform trans);

GLint uniform_float(GLint program, const char * name, float value);

GLint uniform_mat4(GLint program, const char * name, GLsizei count, GLboolean transpose, const GLfloat * value);
