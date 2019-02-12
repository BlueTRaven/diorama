#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

GLint program_general;

bool draw_wireframe;

void game_loop();

void error_callback(int error, const char* description);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void resize_callback(GLFWwindow* window, int width, int height);
