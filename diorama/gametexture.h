#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <stdio.h>
#include <vector>

#include "variables.h"
#include "gamemath.h"
#include "shader.h"

extern std::vector<Decl> assets;

struct texture
{
	std::string name;
	std::string location;
	std::string extention;

	GLuint gl_pointer;

	Shader shader;

	vec2 size;
};

texture* load_get_texture(std::string tex_name);

bool load_texture(std::string tex_name);
