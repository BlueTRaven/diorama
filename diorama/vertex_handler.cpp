#include "vertex_handler.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

using namespace std;

//size of vertex allocation, in byte
const int NUM_VERTEX_ALLOCATED = 3;	//only 3 for now to test one triangle
const int VERTEX_ALLOC_SIZE = NUM_VERTEX_ALLOCATED * sizeof(Vertex);

Vertex vertices[NUM_VERTEX_ALLOCATED];

static size_t last_allocated;

GLuint vertex_array;
GLuint vertex_buffer;

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
	vertices[0].color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	vertices[1] = Vertex();
	vertices[1].position = vec3(0.0f, -1.0f, 0.0f);
	vertices[1].color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	vertices[2] = Vertex();
	vertices[2].position = vec3(1.0f, 1.0f, 0.0f);
	vertices[2].color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_ALLOC_SIZE, &vertices); 
}

void add_vertex(Vertex vertex)
{
	last_allocated++;

	vertices[last_allocated] = vertex;
}
