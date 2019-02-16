#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "diorama.h"
#include "main.h"
#include "shader.h"
#include "variables.h"
#include "vertex_handler.h"
#include "gametexture.h"
#include "input.h"
#include "logging.h"

std::vector<Decl> assets;

int main()
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		printf("GLFW init failed.");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);

	if (!window)
	{
		printf("GLFW Window init failed.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	init_input();

	assets = load_variable_file("Assets/assets.variables");

	std::map<std::string, Decl> cube_types = get_map_of_type("cube", assets);

	std::vector<Decl> vertex_shader_assets = get_all_decl_of_type("vertex_shader", assets); 
	std::vector<Decl> fragment_shader_assets = get_all_decl_of_type("fragment_shader", assets);

	compile_all_shaders(vertex_shader_assets);
	compile_all_shaders(fragment_shader_assets);

	program_general = glCreateProgram();
	link_all_shaders(program_general);

	diorama_init(cube_types);

	while (!glfwWindowShouldClose(window))
	{
		game_loop();
	}

	glfwTerminate();
	return 0;
}

void game_loop()
{
	update_input();
	glfwPollEvents();

	diorama_update();

	diorama_draw();
}

void error_callback(int error, const char* description)
{
	printf("%i, %s\n", error, description);
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	recieve_key_callback(window, key, scancode, action, mods);
}

void resize_callback(GLFWwindow* window, int width, int height) 
{

}
