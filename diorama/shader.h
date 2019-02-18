#pragma once

#include "variables.h"

#include <string>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct vert_attribute
{
	std::string name;
	unsigned int elements;
	size_t size;
	void* offset;

	vert_attribute()
	{
		name = "";
		elements = 0;
		size = 0;
		offset = NULL;
	}

	vert_attribute(std::string _name, unsigned int _elements, size_t _size, void *_offset)
	{
		name = _name;
		elements = _elements;
		size = _size;
		offset = _offset;
	}
};

struct Shader
{
	GLuint program;
	std::string name;

	std::vector<vert_attribute> attributes;
};

static bool shaders_initialized;
extern std::map<std::string, Shader> game_shaders;

void compile_all_shaders(std::vector<Decl> &assets);

void link_all_shaders(Shader shader);

GLint compile_shader(GLenum type, std::string filename);
 
