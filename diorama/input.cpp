#include "variables.h"
#include "input.h"

#include <string>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

std::vector<keybind> keybindings;

std::vector<keybind_event*> events;

void init_input()
{
	std::vector<Decl> keybind_decls = load_variable_file("Assets/input.variables");

	for (int i = 0; i < keybind_decls.size(); i++)
	{
		Decl decl = keybind_decls[i];

		keybind bind = keybind();
		bind.name = decl.name;
		bind.type = decl.subtype;
		
		if (decl.parameters.find("key") != decl.parameters.end())
		{
		   bind.key = std::stoi(decl.parameters["key"].value);

		   keybindings.push_back(bind);
		}
		else 
		{
			printf("Could not load keybinding %s.", decl.name.c_str());
			continue;
		}
	}	
}

void update_input()
{
	for (int i = 0; i < keybindings.size(); i++)
	{
		keybind bind = keybindings[i];
		
		if (bind.state == INPUT_PRESS)
		{
			bind.state = INPUT_HOLD;
			keybind_updated(bind);
		}

		if (bind.state == INPUT_RELEASE)
		{
			bind.state = INPUT_NONE;	
			keybind_updated(bind);
		}
	}
}

void recieve_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	for (int i = 0; i < keybindings.size(); i++)
	{
		keybind bind = keybindings[i];

		if (bind.key == key)
		{
			if (bind.state == INPUT_NONE && action == GLFW_PRESS)
			{
				bind.state = INPUT_PRESS;
				keybind_updated(bind);
			}
			
			if (bind.state != INPUT_NONE && action == GLFW_RELEASE)
			{
				bind.state = INPUT_RELEASE;
				keybind_updated(bind);
			}
		}
	}
}

void keybind_updated(keybind bind)
{
	for (int i = 0; i < events.size(); i++)
	{
		keybind_event *event = events[i];

		event->keybind_updated(bind);
	}	

	printf("keybind %s updated to state %i.\n", bind.name.c_str(), bind.state);
}
