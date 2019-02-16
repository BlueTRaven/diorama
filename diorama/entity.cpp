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
#include "game.h"

void entity_init(entity *ent, transform _trans) 
{
	ent->trans = _trans;

	ent->flags = 0;
}

void entity_draw(entity *ent)
{
	if (ent->vert_array != NULL)
		draw_vertdata(ent->vert_array, ent->trans);
}

void cube_init(entity *ent, cube *c) 
{
	c->ent = ent;

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

	c->ent->vert_array = arr;
}

void cube_update(cube *c, float time)
{
	if ((c->ent->flags & CUBE_SELECTED) == CUBE_SELECTED)
		c->ent->vert_array->draw_flags |= c->ent->vert_array->DRAW_WIREFRAME;
	else
		c->ent->vert_array->draw_flags = c->ent->vert_array->draw_flags & ~c->ent->vert_array->DRAW_WIREFRAME;
}

void player_init(entity *ent, player *pl)
{
	pl->ent = ent;

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

	pl->ent->vert_array = arr;
}

void player_update(player *pl, float time)
{
	pl->ent->trans.origin = pl->ent->trans.position * -1 - vec3(0.5f);
	pl->ent->trans.rotation.y = camera_transform.rotation.y;
}


void player_keybind_updated(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], keybind bind)
{
	if ((bind.state == INPUT_PRESS) && bind.name == "forward")
		pl->ent->trans.position.z -= 1;
	if ((bind.state == INPUT_PRESS) && bind.name == "backward")
		pl->ent->trans.position.z += 1;
	if ((bind.state == INPUT_PRESS) && bind.name == "left")
		pl->ent->trans.position.x -= 1;
	if ((bind.state == INPUT_PRESS) && bind.name == "right")		
		pl->ent->trans.position.x += 1;
}

void player_move_to_tile(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], cube *to_tile)
{

}

bool player_can_move_to_tile(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], cube *to_tile)
{
	return tiles[(int)to_tile->ent->trans.position.x][(int)to_tile->ent->trans.position.y][(int)to_tile->ent->trans.position.z] != NULL; 
}
