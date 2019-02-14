#include <vector>

#include "vertex_handler.h"
#include "gamemath.h"
#include "entity.h"
#include "drawing.h"

#include "gametexture.h"

#include "colors.h"

void entity::init(transform _trans) 
{
	this->trans = _trans;
}

void entity::update(float time) { }

void entity::draw()
{
	if (this->vertices != NULL)
		draw_vertdata(this->vertices, this->trans);
}

void cube::init(transform _trans) 
{
	entity::init(_trans);

	vertex_array *arr = new vertex_array();

	std::vector<Vertex> vertices;
	//front side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), WHITE)); 
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), WHITE));

	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), WHITE));

	//right side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));
	
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), WHITE));

	//back side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));

	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE)); 

	//left side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), WHITE));
	
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));

	add_vertices(arr, vertices, loaded_textures["dirt_grass_side_01"]);

	vertices.clear();

	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f), WHITE));	//back left
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));	//front right
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));	//front left

	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f), WHITE));	//back left
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));	//back right
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));	//front right

	add_vertices(arr, vertices, loaded_textures["grass_01"]);
	create_vertex_array(arr);

	this->vertices = arr;
}
