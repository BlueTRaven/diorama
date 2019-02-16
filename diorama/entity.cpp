#include <vector>
#include <math.h>

#include "vertex_handler.h"
#include "gamemath.h"
#include "entity.h"
#include "drawing.h"
#include "gametexture.h"
#include "colors.h"
#include "input.h"
#include "camera.h"

void entity::init(transform _trans) 
{
	this->trans = _trans;

	this->flags = 0;
}

void entity::update(float time) { }

void entity::draw()
{
	if (this->vert_array != NULL)
		draw_vertdata(this->vert_array, this->trans);
}

void entity::on_kill() { }

void cube::init(transform _trans) 
{
	entity::init(_trans);

	vertex_array *arr = new vertex_array();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//front side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), WHITE)); 
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), WHITE));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	add_vertices(arr, vertices, indices, loaded_textures["dirt_grass_side_01"]);

	vertices.clear();
	indices.clear();
	
	//right side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f), WHITE));

	indices.push_back(4 + 0);
	indices.push_back(4 + 1);
	indices.push_back(4 + 2);

	indices.push_back(4 + 2);
	indices.push_back(4 + 3);
	indices.push_back(4 + 0);
	
	add_vertices(arr, vertices, indices, loaded_textures["dirt_grass_side_01"]);

	vertices.clear();
	indices.clear();
	
	//back side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));

	indices.push_back(8 + 0);
	indices.push_back(8 + 1);
	indices.push_back(8 + 2);

	indices.push_back(8 + 2);
	indices.push_back(8 + 3);
	indices.push_back(8 + 0);
	
	add_vertices(arr, vertices, indices, loaded_textures["dirt_grass_side_01"]);

	vertices.clear();
	indices.clear();
	
	//left side
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));

	indices.push_back(12 + 0);
	indices.push_back(12 + 1);
	indices.push_back(12 + 2);

	indices.push_back(12 + 2);
	indices.push_back(12 + 3);
	indices.push_back(12 + 0);
	
	add_vertices(arr, vertices, indices, loaded_textures["dirt_grass_side_01"]);

	vertices.clear();
	indices.clear();

	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f), WHITE));	//back left
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));	//front right
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));	//front left
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f), WHITE));	//back right

	indices.push_back(16 + 0);
	indices.push_back(16 + 1);
	indices.push_back(16 + 2);

	indices.push_back(16 + 0);
	indices.push_back(16 + 3);
	indices.push_back(16 + 1);
	
	add_vertices(arr, vertices, indices, loaded_textures["grass_01"]);
	create_vertex_array(arr);

	this->vert_array = arr;
}

void cube::update(float time)
{
	if ((flags & SELECTED) == SELECTED)
		this->vert_array->draw_flags |= this->vert_array->DRAW_WIREFRAME;
	else
		this->vert_array->draw_flags = this->vert_array->draw_flags & ~this->vert_array->DRAW_WIREFRAME;
}

void player::init(transform _trans)
{
	entity::init(_trans);

	vertex_array *arr = new vertex_array();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//front side
	vertices.push_back(Vertex(vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), WHITE));
	vertices.push_back(Vertex(vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), WHITE));
	vertices.push_back(Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), WHITE));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);
	
	add_vertices(arr, vertices, indices, loaded_textures["dirt_grass_side_01"]);

	create_vertex_array(arr);

	this->vert_array = arr;
}

void player::update(float time)
{
	this->trans.origin = this->trans.position * -1 - vec3(0.5f);
	this->trans.rotation.y = camera_transform.rotation.y;
}

void player::on_kill()
{

}

static void keybind_updated(entity *e, keybind bind)
{
	if (typeof(e) == typeof(player))
	if ((bind.state == INPUT_PRESS) && bind.name == "forward")
		e->trans.position.z += 1;
	if ((bind.state == INPUT_PRESS) && bind.name == "backward")
		e->trans.position.z -= 1;
	if ((bind.state == INPUT_PRESS) && bind.name == "left")
		e->trans.position.x -= 1;
	if ((bind.state == INPUT_PRESS) && bind.name == "right")		
		e->trans.position.x += 1;
}

