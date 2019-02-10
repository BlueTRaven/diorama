#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "vertex_handler.h"
#include "gamemath.h"
#include "logging.h"
#include "entity.h"

#include <stdio.h>
using namespace std;

vector<entity*> entities;

void diorama_init()
{
	entities.push_back(new cube());

	init_entities();
}

void init_entities()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->init(entities[i]);
	}
}

void update()
{
	double time = glfwGetTime();
}

void update_input()
{
	glfwPollEvents();
}

void draw()
{
	GLFWwindow *window = glfwGetCurrentContext();

	int width, height;
	float ratio;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw_world(width, height, ratio);

	glfwSwapBuffers(window);
}

void draw_world(int width, int height, float ratio)
{
	glUseProgram(program_general);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_arrays[0]->vert_buffer);

	GLint attrib_position = vertex_attribute(program_general, "position", 3, sizeof(Vertex), (void*)0);
	GLint attrib_tex_coord = vertex_attribute(program_general, "tex_coord", 2, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	GLint attrib_color = vertex_attribute(program_general, "color", 4, sizeof(Vertex), (void*)offsetof(Vertex, color));

	mat4x4 * matrix = get_perspective(width, height, 1.0f, 1000.0f, 30.0f);

	uniform_mat4(program_general, "projection", 1, false, matrix->m); 

	for (int i = 0; i < vertex_arrays[0]->datas.size(); i++)
	{
		vector<vertex_data> datas = vertex_arrays[0]->datas;
		if (draw_wireframe)
			glDrawArrays(GL_LINE_STRIP, datas[i].start, datas[i].size); 
		else glDrawArrays(GL_TRIANGLES, datas[i].start, datas[i].size); 
	}

	disable_vertex_attribute(attrib_position);
	disable_vertex_attribute(attrib_tex_coord);
	disable_vertex_attribute(attrib_color);
}
