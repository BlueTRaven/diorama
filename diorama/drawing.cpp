#include "vertex_handler.h"
#include "gamemath.h"

#include "drawing.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

void draw_vertdata(vertex_data *data, transform *trans)
{
	mat4x4 matrix = trans->matrix();
	uniform_mat4(program_general, "object", 1, true, matrix.m); 	
	
	if (draw_wireframe)
		glDrawArrays(GL_LINE_STRIP, data->start, data->size);
	else glDrawArrays(GL_TRIANGLES, data->start, data->size);
}