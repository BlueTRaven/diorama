#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <stdio.h>
#include <string>

bool glerrors_endlisten(std::string description)
{
	bool any_err = false;

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		any_err = true;
		printf("Encountered OpenGL error during '%s'. error: 0x%X\n", description.c_str(), err);
	}	

	return any_err;
}

void glerrors_startlisten()
{	//stub to simply clear the error queue
	while(true) 
	{
		if (glGetError() == GL_NO_ERROR)
			break;
	}
}
