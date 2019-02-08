#include "vertex_handler.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

using namespace std;

GLuint vertex_array;
GLuint vertex_buffer;

//size of vertex allocation, in byte
const int NUM_VERTEX_ALLOCATED = 3;	//only 3 for now to test one triangle
const int VERTEX_ALLOC_SIZE = NUM_VERTEX_ALLOCATED * sizeof(Vertex);

Vertex vertices[NUM_VERTEX_ALLOCATED];

static size_t last_allocated;

void init_vertex_buffers()
{
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_ALLOC_SIZE, vertices, GL_STATIC_DRAW);

	//this is here for testing purposes
	vertices[0] = Vertex();
	vertices[0].position = vec3(-1.0f, 1.0f, 1.0f);
	vertices[0].color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1] = Vertex();
	vertices[1].position = vec3(0.0f, -1.0f, 0.0f);
	vertices[1].color = vec4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2] = Vertex();
	vertices[2].position = vec3(1.0f, 1.0f, 0.0f);
	vertices[2].color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_ALLOC_SIZE, &vertices); 
}

void add_vertex(Vertex vertex)
{
	last_allocated++;

	vertices[last_allocated] = vertex;
}

int last_error = 0;
const char * last_name;

GLint vertex_attribute(GLint program, const char * name, GLint fields, GLsizei size, void * offset)
{
	GLint attrib = glGetAttribLocation(program, name);
	
	if (fields > 4 && last_error != attrib && last_name != name)
	{
		printf("Cannot have more than 4 fields. Was given %i.\n", fields);

		last_error = attrib;
		last_name = (char*)name;

		return -1;
	}

	if (attrib == -1 && last_error != attrib && last_name != name)
	{
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

float * mat4x4_to_array(mat4x4 matrix)
{
	float * arr = new float[16]
	{
		matrix.a, matrix.b, matrix.c, matrix.d,
		matrix.e, matrix.f, matrix.g, matrix.h,
		matrix.i, matrix.j, matrix.k, matrix.l,
		matrix.m, matrix.n, matrix.o, matrix.p,
	};

	return &arr[0];
}

mat4x4 get_identity()
{
	mat4x4 matrix = mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
					   	   0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f);

	return matrix;	
}
