#include "vertex_handler.h"
#include "gamemath.h"

#include "drawing.h"
#include "game.h"
#include "camera.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

int last_error_uniform;
const char * last_name_uniform;

void draw_vertdata(vertex_array *vert_array, transform trans)
{
	glBindVertexArray(vert_array->vert_array);
	glBindBuffer(GL_ARRAY_BUFFER, vert_array->vert_buffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vert_array->index_buffer);

	/*GLint attrib_position = vertex_attribute(program_general, "position", 3, sizeof(Vertex), (void*)0);
	GLint attrib_tex_coord = vertex_attribute(program_general, "tex_coord", 2, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	GLint attrib_color = vertex_attribute(program_general, "color", 4, sizeof(Vertex), (void*)offsetof(Vertex, color));*/

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	std::vector<GLint> attribute_positions;

	if (vert_array->draw_flags & vert_array->DRAW)
	{	
		for (int i = 0; i < vert_array->datas.size(); i++)
		{
			vertex_data *data = vert_array->datas[i];

			texture *tex = data->tex;

			glUseProgram(tex->shader.program);

			uniform_vec4(tex->shader.program, "tint_color", vert_array->tint);

			mat4x4 matrix = trans.matrix();
			uniform_mat4(tex->shader.program, "object", 1, true, matrix.m); 	
			
			set_pers_and_camera(tex->shader.program, 0);

			for (int i = 0; i < tex->shader.attributes.size(); i++)
			{	//TODO some sort of attribute caching? check if name and location are the same and only change then?
				vert_attribute attrib = tex->shader.attributes[i];

				GLint vert_attrib = vertex_attribute(tex->shader.program, attrib.name.c_str(), attrib.elements, attrib.size, attrib.offset);

				attribute_positions.push_back(vert_attrib);
			}

			if (vert_array->draw_flags & vert_array->DRAW_TEXTURE)
			{
				glBindTexture(GL_TEXTURE_2D, data->tex->gl_pointer);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}

			glDrawElements(GL_TRIANGLES, data->size, GL_UNSIGNED_INT, (void*)(data->start * sizeof(unsigned int)));
		}
	}

	glDisable(GL_DEPTH_TEST);

	if (vert_array->draw_flags & vert_array->DRAW_WIREFRAME)	
	{
		for (int i = 0; i < vert_array->datas.size(); i++)
		{
			vertex_data *data = vert_array->datas[i];

			glBindTexture(GL_TEXTURE_2D, 0);
			glDrawElements(GL_LINE_STRIP, data->size, GL_UNSIGNED_INT, (void*)(data->start * sizeof(unsigned int)));
		}
	}	

	for (int i = 0; i < attribute_positions.size(); i++)
	{
		disable_vertex_attribute(attribute_positions[i]);
	}

	/*disable_vertex_attribute(attrib_position);
	disable_vertex_attribute(attrib_tex_coord);
	disable_vertex_attribute(attrib_color);	*/
}

void set_pers_and_camera(GLint program, int projection_type)
{
	float pers_near = 1.0f;
	float pers_far = 1000.0f;

	float top, bottom, left, right;
	compute_screen_coordinates(45, (float)width_current / (float)height_current, pers_near, pers_far, left, right, top, bottom);
	mat4x4 matrix = get_perspective(left, right, top, bottom, pers_near, pers_far);

	uniform_mat4(program, "projection", 1, true, matrix.m); 
	uniform_mat4(program, "camera", 1, true, camera_get_matrix().m); 
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

GLint uniform_vec4(GLint program, const char *name, vec4 value)
{
	GLint uniform = glGetUniformLocation(program, name);
	if (uniform == -1 && last_error_uniform != uniform && last_name_uniform != name)
	{
		printf("Could not find uniform %s position.\n", name);
		
		last_error_uniform = uniform;
		last_name_uniform = name;

		return -1;
	}

	glUniform4f(uniform, value.x, value.y, value.z, value.w);

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
