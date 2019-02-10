#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

using namespace std;

vector<vertex_array*> vertex_arrays; 

static int last_allocated;

void init_vertex_buffers()
{
	int total_arrays = 1;

	vertex_arrays = vector<vertex_array*>();

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
/*	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_ALLOC_SIZE, vertices, GL_STATIC_DRAW);*/

	//this is here for testing purposes
/*	vertices[0] = Vertex();
	vertices[0].position = vec3(-1.0f, 1.0f, -8.0f);
	vertices[0].color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1] = Vertex();
	vertices[1].position = vec3(0.0f, -1.0f, -8.0f);
	vertices[1].color = vec4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2] = Vertex();
	vertices[2].position = vec3(1.0f, 1.0f, -8.0f);
	vertices[2].color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_ALLOC_SIZE, &vertices);*/

	vector<Vertex> vertices = vector<Vertex>();
	vertices.push_back(Vertex(vec3(-1.0f, 1.0f, -8.0f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, -8.0f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices.push_back(Vertex(vec3(0.0f, -1.0f, -8.0f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	add_vertices(vertices, 0);
}

vertex_data *add_vertices(vector<Vertex> add_vertices, int to_array)
{
	int end = last_allocated + add_vertices.size();
	while(true)
	{
		if (last_allocated > MAX_VERTEX)
			last_allocated = 0;

		bool valid = true;

		for (int i = last_allocated; i < end; i++)
		{
			Vertex *vert = vertex_arrays[to_array]->vertices;
			if (vert->position.x != 0 || vert->position.y != 0 || vert->position.z != 0)
			{
				valid = false;
				break;
			}
			/*if (vertex_arrays[to_array]->vertices[i].valid) 
			{	
				valid = false;
				break;
			}*/
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

	vertex_arrays[to_array]->datas.push_back(*ret);

	glBindVertexArray(vertex_arrays[to_array]->vert_array);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_arrays[to_array]->vert_buffer);
//	glBufferSubData(GL_ARRAY_BUFFER, ret->start, ret->end - ret->start, &vertex_arrays[to_array]->vertices);
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

int last_error_uniform;
const char * last_name_uniform;

GLint uniform_float(GLint program, const char * name, float value)
{
	GLint uniform = glGetUniformLocation(program, name);
	if (uniform == -1 && last_error_uniform != uniform && last_name_uniform != name)
	{
		printf("Could not find uniform %s position.\n", name);
		
		last_error_uniform = uniform;
		last_name_uniform = name;

		return -1;
	}

	glUniform1f(uniform, value);

	return uniform;
}

GLint uniform_mat4(GLint program, const char * name, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	GLint uniform = glGetUniformLocation(program, name);
	if (uniform == -1)
	{
		printf("Could not find uniform %s position.\n", name);
		return -1;
	}

	glUniformMatrix4fv(uniform, count, transpose, value);

	return uniform;
}

void disable_vertex_attribute(GLint attribute)
{
	if (attribute > 0)
		glDisableVertexAttribArray(attribute);
}

