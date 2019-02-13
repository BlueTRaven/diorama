#include <vector>

#include "vertex_handler.h"
#include "gamemath.h"
#include "entity.h"
#include "drawing.h"

#include "gametexture.h"

#include "colors.h"

void entity::init(transform *_trans) 
{
	this->trans = _trans;
}

void entity::update(float time) { }

void entity::draw()
{
	if (this->vertices != NULL)
		draw_vertdata(this->vertices, this->trans);
}

void cube::init(transform *_trans) 
{
	entity::init(_trans);
	this->trans->origin = vec3(0.5f) * -1;

	std::vector<Vertex> vertices;
	//front side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), RED)); 
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), RED));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), RED));

	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), RED));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), RED));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), RED));

	//right side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), GREEN));
	
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), GREEN));

	//back side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), BLUE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), BLUE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), BLUE));

	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), BLUE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), BLUE));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), BLUE)); 

	//left side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), WHITE));
	
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));

	this->vertices = add_vertices(vertices, loaded_textures["player"], 0);
}

void cube::update(float time)
{
	if (this->rotate)
		this->trans->rotation.y++;
}
