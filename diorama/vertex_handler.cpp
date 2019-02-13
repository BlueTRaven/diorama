#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

std::vector<vertex_array*> vertex_arrays; 

static int last_allocated;

void init_vertex_buffers()
{
	int total_arrays = 1;

	vertex_arrays = std::vector<vertex_array*>();

	for (int i = 0; i < total_arrays; i++)
	{
		vertex_array * arr = new vertex_array();	//TODO to new

		glGenVertexArrays(i + 1, &arr->vert_array);
		glBindVertexArray(arr->vert_array);

		glGenBuffers(i + 1, &arr->vert_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, arr->vert_buffer);
		glBufferData(GL_ARRAY_BUFFER, VERTEX_ALLOC_SIZE, arr->vertices, GL_STATIC_DRAW);

		vertex_arrays.push_back(arr);
	}
}

vertex_data *add_vertices(std::vector<Vertex> add_vertices, texture *tex, int to_array)
{
	int end = last_allocated + add_vertices.size();
	while(true)
	{
		if (last_allocated > MAX_VERTEX)
			last_allocated = 0;

		bool valid = true;

		for (int i = last_allocated; i < end; i++)
		{
			if (vertex_arrays[to_array]->vertices[i].valid) 
			{	
				valid = false;
				break;
			}
		}

		if (valid) break;

		//TODO break out of potential infinite loop here	
		last_allocated++;

		end = last_allocated + add_vertices.size();
	}

	//if we get to this point, it means we've found a place for this.
	for (int i = last_allocated; i < end; i++)
		vertex_arrays[to_array]->vertices[i] = add_vertices[i - last_allocated];

	vertex_data * ret = new vertex_data();
	ret->arr = to_array;
	ret->start = last_allocated;
	ret->size = add_vertices.size(); 
	
	ret->datas_index = vertex_arrays[to_array]->datas.size();

	ret->tex = tex;

	vertex_arrays[to_array]->datas.push_back(*ret);

	glBindVertexArray(vertex_arrays[to_array]->vert_array);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_arrays[to_array]->vert_buffer);
	//glBufferSubData(GL_ARRAY_BUFFER, ret->start, ret->size, &vertex_arrays[to_array]->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_ALLOC_SIZE, &vertex_arrays[to_array]->vertices);

	return ret;
}

int last_error = 0;
const char * last_name;

GLint vertex_attribute(GLint program, const char * name, GLint fields, GLsizei size, void * offset)
{
	GLint attrib = glGetAttribLocation(program, name);

	if (fields > 4)
	{
		if (last_error != attrib && last_name != name)
			printf("Cannot have more than 4 fields. Was given %i.\n", fields);

		last_error = attrib;
		last_name = (char*)name;

		return -1;
	}

	if (attrib == -1) 
	{
		if (last_error != attrib && last_name != name)
			printf("Could not find attribute %s position.\n", name);

		last_error = attrib;
		last_name = (char*)name;

		return -1;
	}

	glEnableVertexAttribArray(attrib);

	glVertexAttribPointer(attrib, fields, GL_FLOAT, GL_FALSE, size, offset);

	glBindAttribLocation(program, attrib, name);

	return attrib;
}

void disable_vertex_attribute(GLint attribute)
{
	if (attribute > 0)
		glDisableVertexAttribArray(attribute);
}

