#pragma once

#include "variables.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void compile_all_shaders(std::vector<Decl> &assets);

void link_all_shaders(GLuint program);

GLint compile_shader(GLenum type, std::string filename);
