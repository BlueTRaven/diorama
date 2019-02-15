#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

std::vector<vertex_array*> vertex_arrays; 

//create vertex array: new vertex_array();
//create Vertices, pass with array to add_vertices
//call this function
void create_vertex_array(vertex_array *arr)
{
	glGenVertexArrays(1, &arr->vert_array);
	glBindVertexArray(arr->vert_array);

	glGenBuffers(1, &arr->vert_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, arr->vert_buffer);
	glBufferData(GL_ARRAY_BUFFER, arr->vertices.size() * sizeof(Vertex), arr->vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &arr->index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arr->index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr->indices.size() * sizeof(unsigned int), arr->indices.data(), GL_STATIC_DRAW);

	//update the datas to have to correct array
	for (int i = 0; i < arr->datas.size(); i++)
		arr->datas[i]->arr = vertex_arrays.size();	

	vertex_arrays.push_back(arr);
}

void add_vertices(vertex_array *vert_array, std::vector<Vertex> add_vertices, std::vector<unsigned int> indices, texture *tex)
{
	int index = vert_array->indices.size();

	//std::copy(add_vertices.begin(), add_vertices.end(), std::back_inserter(vert_array->vertices));

	for (int i = 0; i < add_vertices.size(); i++)
		vert_array->vertices.push_back(add_vertices[i]);
	for (int i = 0; i < indices.size(); i++)
		vert_array->indices.push_back(indices[i]);

	vertex_data * ret = new vertex_data();
	ret->start = index; 
	ret->size = indices.size(); 
	
	ret->tex = tex;

	ret->datas_index = vert_array->datas.size();

	vert_array->datas.push_back(ret);
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

