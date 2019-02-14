#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <stdio.h>

bool printf_glerrors()
{
	bool any_err = false;

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		any_err = true;
		printf("Encountered OpenGL error: 0x%X\n", err);
	}	

	return any_err;
}

void clear_glerrors()
{	//stub to simply clear the error queue
	while(true) 
	{
		if (glGetError() == GL_NO_ERROR)
			break;
	}
}
