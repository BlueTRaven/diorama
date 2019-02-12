#include <vector>

#include "vertex_handler.h"
#include "gamemath.h"
#include "entity.h"
#include "drawing.h"

#include "colors.h"

void entity::init() 
{
	this->trans = new transform();
	this->trans->position = vec3();
	this->trans->scale = vec3(1.0f, 1.0f, 1.0f);
	this->trans->rotation = vec3();
}

void entity::update() { }

void entity::draw()
{
	if (this->vertices != NULL)
		draw_vertdata(this->vertices, this->trans);
}

void cube::init() 
{
	entity::init();
	//this->trans->position = vec3(0.0f, 0.0f, -5.0f);
	std::vector<Vertex> vertices;
	//front side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0), vec2(0.0f, 0.0f), RED)); 
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0), vec2(0.0f, 0.0f), RED));
	vertices.push_back(Vertex(vec3(0.0f, -1.0f, 0), vec2(0.0f, 0.0f), RED));

	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0), vec2(0.0f, 0.0f), RED));
	vertices.push_back(Vertex(vec3(1.0f, -1.0f, 0), vec2(0.0f, 0.0f), RED));
	vertices.push_back(Vertex(vec3(0.0f, -1.0f, 0), vec2(0.0f, 0.0f), RED));

	//right side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0), vec2(0.0f, 0.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f), GREEN));
	
	vertices.push_back(Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, -1.0f, 0), vec2(0.0f, 0.0f), GREEN));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0), vec2(0.0f, 0.0f), GREEN));

	//back side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f), BLUE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f), BLUE));
	vertices.push_back(Vertex(vec3(0.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f), BLUE));

	vertices.push_back(Vertex(vec3(0.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f), BLUE));
	vertices.push_back(Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f), BLUE));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f), BLUE)); 

	//left side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, -1.0f, 0), vec2(0.0f, 0.0f), WHITE));
	
	vertices.push_back(Vertex(vec3(0.0f, -1.0f, 0), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f), WHITE));

	this->vertices = add_vertices(vertices, 0);
}

void cube::update()
{
	this->trans->rotation.y++;
}

void cube::draw()
{
	draw_vertdata(this->vertices, this->trans);
}
