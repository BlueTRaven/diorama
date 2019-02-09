#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "vertex_handler.h"
#include "gamemath.h"

#include <stdio.h>
using namespace std;

void update()
{
	double time = glfwGetTime();
}

void update_input()
{
	glfwPollEvents();
}

void draw(GLint program)
{
	GLFWwindow *window = glfwGetCurrentContext();

	int width, height;
	float ratio;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_arrays[0]->vert_buffer);

	GLint attrib_position = vertex_attribute(program, "position", 3, sizeof(Vertex), (void*)0);
	GLint attrib_tex_coord = vertex_attribute(program, "tex_coord", 2, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	GLint attrib_color = vertex_attribute(program, "color", 4, sizeof(Vertex), (void*)offsetof(Vertex, color));

	mat4x4 * matrix = get_identity(); //get_perspective(width, height, 1.0f, 1000.0f, 30.0f);

	uniform_mat4(program, "projection", 1, false, matrix->m); 

	for (int i = 0; i < vertex_arrays[0]->datas.size(); i++)
		glDrawArrays(GL_TRIANGLES, vertex_arrays[0]->datas[i].start, vertex_arrays[0]->datas[i].size); 
	//glDrawArrays(GL_TRIANGLES, 0, 3);

 	glDisableVertexAttribArray(attrib_position);
	glDisableVertexAttribArray(attrib_tex_coord);
	glDisableVertexAttribArray(attrib_color);

	glfwSwapBuffers(window);
}
