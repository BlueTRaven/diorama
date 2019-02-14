#include "vertex_handler.h"
#include "gamemath.h"

#include "drawing.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

int last_error_uniform;
const char * last_name_uniform;

void draw_vertdata(vertex_array *vert_array, transform trans)
{
	glBindVertexArray(vert_array->vert_array);
	glBindBuffer(GL_ARRAY_BUFFER, vert_array->vert_buffer);

	GLint attrib_position = vertex_attribute(program_general, "position", 3, sizeof(Vertex), (void*)0);
	GLint attrib_tex_coord = vertex_attribute(program_general, "tex_coord", 2, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	GLint attrib_color = vertex_attribute(program_general, "color", 4, sizeof(Vertex), (void*)offsetof(Vertex, color));
	
	mat4x4 matrix = trans.matrix();
	uniform_mat4(program_general, "object", 1, true, matrix.m); 	
		
	for (int i = 0; i < vert_array->datas.size(); i++)
	{
		vertex_data *data = vert_array->datas[i];

		glBindTexture(GL_TEXTURE_2D, data->tex->gl_pointer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		if (draw_wireframe)
			glDrawArrays(GL_LINE_STRIP, data->start, data->size);
		else glDrawArrays(GL_TRIANGLES, data->start, data->size);
	}

	disable_vertex_attribute(attrib_position);
	disable_vertex_attribute(attrib_tex_coord);
	disable_vertex_attribute(attrib_color);	
}

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
	if (uniform == -1 && last_error_uniform != uniform && last_name_uniform != name)
	{
		printf("Could not find uniform %s position.\n", name);

		last_error_uniform = uniform;
		last_name_uniform = name;

		return -1;
	}

	glUniformMatrix4fv(uniform, count, transpose, value);

	return uniform;
}
