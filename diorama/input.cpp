#include "variables.h"
#include "input.h"

#include <string>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

std::vector<keybind> keybindings;

std::vector<keybind_event*> events;

keybind_event *keybind_subscribe(void (*keybind_updated)(keybind bind))
{
	keybind_event *event = new keybind_event();

	event->index = events.size();
	event->keybind_updated = keybind_updated;	
	events.push_back(event);	
	
	return event;
}

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
		if (keybindings[i].state == INPUT_PRESS || keybindings[i].state == INPUT_HOLD)
		{
			keybindings[i].state = INPUT_HOLD;
			keybind_updated(keybindings[i]);
		}

		if (keybindings[i].state == INPUT_RELEASE)
		{
			keybindings[i].state = INPUT_NONE;	
			keybind_updated(keybindings[i]);
		}
	}
}

void recieve_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	for (int i = 0; i < keybindings.size(); i++)
	{
		if (keybindings[i].key == key)
		{
			if (keybindings[i].state == INPUT_NONE && action == GLFW_PRESS)
			{
				keybindings[i].state = INPUT_PRESS;
				keybind_updated(keybindings[i]);
			}
			
			if (keybindings[i].state != INPUT_NONE && action == GLFW_RELEASE)
			{
				keybindings[i].state = INPUT_RELEASE;
				keybind_updated(keybindings[i]);
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
}
