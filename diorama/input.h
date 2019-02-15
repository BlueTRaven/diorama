#pragma once

#include <string>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

const int INPUT_NONE = 0;
const int INPUT_PRESS = 1;
const int INPUT_HOLD = 2;
const int INPUT_RELEASE = 3;

struct keybind
{
	std::string name;
	std::string type;
	int key;	

	int state;
};

struct keybind_event
{
	void (*keybind_updated)(keybind bind);
	int index;
};

void init_input();

void recieve_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void update_input();
void keybind_updated(keybind bind);