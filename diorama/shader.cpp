#pragma once

#include "variables.h"
#include "shader.h"

#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

static bool compiled_shaders = false;

static vector<GLuint> vertex_shaders;
static vector<GLuint> fragment_shaders;

std::map<std::string, Shader> game_shaders;

void compile_all_shaders(vector<Decl> &assets)
{
	compiled_shaders = true;

	for (int i = 0; i < assets.size(); i++)
	{
		if (assets[i].type != "asset" || (assets[i].subtype != "vertex_shader" && assets[i].subtype != "fragment_shader"))
			printf("Illegal declaration of non-asset type.");

		if (assets[i].subtype == "vertex_shader")
		{
			GLint shader = compile_shader(GL_VERTEX_SHADER, assets[i].parameters["location"].value);
			if (shader != -1)
			{	vertex_shaders.push_back(shader);
				printf("Finished compiling vertex shader %s.\n", assets[i].name.c_str());
			}
			else printf("Vertex shader %s compilation failed.\n", assets[i].name.c_str());
		}
		else if (assets[i].subtype == "fragment_shader")
		{
			GLint shader = compile_shader(GL_FRAGMENT_SHADER, assets[i].parameters["location"].value);
			if (shader != -1)
			{
				fragment_shaders.push_back(shader);
				printf("Finished compiling fragment shader %s.\n", assets[i].name.c_str());
			}
			else printf ("Fragment shader %s compilation failed.\n", assets[i].name.c_str());
		}
	}
}

void link_all_shaders(Shader shader)
{	//TODO do we need to link ALL shaders??

	GLuint program = shader.program;

	if (!compiled_shaders)
	{
		printf("No shaders have been compiled. call compile_all_shaders and pass in some shader asset declarations first.\n");
		return;
	}

	if (vertex_shaders.size() == 0)
		printf("No vertex shaders stored. Call compile_all_shaders and pass in some shader asset declarations first.\n");
	if (fragment_shaders.size() == 0)
		printf("No fragment shaders stored. Call compile_all_shaders and pass in some shader asset declarations first.\n");
		
	if (vertex_shaders.size() == 0 || fragment_shaders.size() == 0)
		return;

	for (size_t i = 0; i < vertex_shaders.size(); i++)
		glAttachShader(program, vertex_shaders[i]);
	for (size_t i = 0; i < fragment_shaders.size(); i++)
		glAttachShader(program, fragment_shaders[i]);

	glLinkProgram(program);

	GLint linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&linked);
	if (linked == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			GLchar * log = new GLchar[length];
			glGetProgramInfoLog(program, length, NULL, log);
			printf("%s\0\n", log);

			//note that we don't detach and delete the shader, because that will be done anyways.
			delete[] log;
		}
	
	}

	for (size_t i = 0; i < vertex_shaders.size(); i++)
	{
		glDetachShader(program, vertex_shaders[i]);
		glDeleteShader(vertex_shaders[i]);
	}
	for (size_t i = 0; i < fragment_shaders.size(); i++)
	{
		glDetachShader(program, fragment_shaders[i]);	
		glDeleteShader(fragment_shaders[i]);
	}

	vertex_shaders.clear();
	fragment_shaders.clear();

	compiled_shaders = false;

	printf("Finished linking shaders to program %s.\n", shader.name.c_str());

	if (!shaders_initialized)
	{
		game_shaders = std::map<std::string, Shader>();
		shaders_initialized = true;
	}
	
	game_shaders.insert(std::make_pair(shader.name, shader));
}

GLint compile_shader(GLenum type, string filename)
{
	ifstream file;

	string directory = "C:/Users/Taylor/Documents/Programming/C++/diorama/diorama/";

	file.open((directory + filename).c_str());

	stringstream strstream;
	strstream << file.rdbuf();
	string full = strstream.str();
	const char * full_c_str = full.c_str();

	GLint shader = glCreateShader(type);
	glShaderSource(shader, 1, &full_c_str, NULL);
	glCompileShader(shader);
	
	GLint length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		GLchar * log = new GLchar[length];
		glGetShaderInfoLog(shader, length, NULL, log);

		printf("%s\0\n", log);

		glDeleteShader(shader);
		shader = -1;
		delete[] log;
	}

	return shader;
}
