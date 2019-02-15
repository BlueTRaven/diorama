#pragma once

#include "gamemath.h"
#include "gametexture.h"

#include <vector>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

const int MAX_VERTEX = 1024;
const int VERTEX_ALLOC_SIZE = MAX_VERTEX * sizeof(Vertex);

struct vertex_data
{
	int arr;	//opengl array pointer
	int datas_index;	//index in array.datas where we are

	int start;	//start offset in the array
	int size;	//size, in vertices

	texture *tex;	//texture bound to these vertices
};

struct vertex_array
{
	GLuint vert_array;
	GLuint vert_buffer;
	GLuint index_buffer;

	vec4 tint;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	std::vector<vertex_data*> datas;
	
	vertex_array()
	{
		vert_array = 0;
		vert_buffer = 0;

		tint = vec4(1.0f);
	}
};

void create_vertex_array(vertex_array *arr);

void add_vertices(vertex_array *vert_array, std::vector<Vertex> add_vertices, std::vector<unsigned int> indices, texture *tex);

GLint vertex_attribute(GLint program, const char * name, GLint fields, GLsizei size, void * offset);

void disable_vertex_attribute(GLint attribute);

GLint uniform_float(GLint program, const char * name, float value);

GLint uniform_mat4(GLint program, const char * name, GLsizei count, GLboolean transpose, const GLfloat * value);
