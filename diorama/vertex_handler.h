#pragma once

#include "gamemath.h"

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
};

struct vertex_array
{
	GLuint vert_array;
	GLuint vert_buffer;

	Vertex vertices[MAX_VERTEX];

	std::vector<vertex_data> datas;
	
	vertex_array()
	{
		vert_array = 0;
		vert_buffer = 0;
	}
};

void init_vertex_buffers();

vertex_data *add_vertices(std::vector<Vertex> add_vertices, int to_array);

GLint vertex_attribute(GLint program, const char * name, GLint fields, GLsizei size, void * offset);

void disable_vertex_attribute(GLint attribute);

GLint uniform_float(GLint program, const char * name, float value);

GLint uniform_mat4(GLint program, const char * name, GLsizei count, GLboolean transpose, const GLfloat * value);
