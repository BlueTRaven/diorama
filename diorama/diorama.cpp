#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "vertex_handler.h"

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

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	
	//GLint attrib_position = glGetAttribLocation(program, "position");
	//GLint attrib_tex_coord = glGetAttribLocation(program, "tex_coord");
	//GLint attrib_color = glGetAttribLocation(program, "color");

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "tex_coord");
	glBindAttribLocation(program, 2, "color");

	glDrawArrays(GL_TRIANGLES, 0, 3);

 	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glfwSwapBuffers(window);
}
