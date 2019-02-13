#include "vertex_handler.h"
#include "gamemath.h"

#include "drawing.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

int last_error_uniform;
const char * last_name_uniform;

void draw_vertdata(vertex_data *data, transform *trans)
{
	mat4x4 matrix = trans->matrix();
	uniform_mat4(program_general, "object", 1, true, matrix.m); 	
		
	glBindTexture(GL_TEXTURE_2D, data->tex->gl_pointer);
	if (draw_wireframe)
		glDrawArrays(GL_LINE_STRIP, data->start, data->size);
	else glDrawArrays(GL_TRIANGLES, data->start, data->size);
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
