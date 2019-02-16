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

void cube_init(entity *ent, cube *c, Decl cube_asset) 
{
	c->ent = ent;
	c->type = cube_asset.name;

	if (c->type == "air")
	{	//air is a special case! it's just kind of there, no vertices or anything.
		return;
	}

	texture *tex_n = load_get_texture(cube_asset.parameters["side_n"].value);
	texture *tex_s = load_get_texture(cube_asset.parameters["side_s"].value);
	texture *tex_e = load_get_texture(cube_asset.parameters["side_e"].value);
	texture *tex_w = load_get_texture(cube_asset.parameters["side_w"].value);
	texture *tex_u = load_get_texture(cube_asset.parameters["side_u"].value);

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

	add_vertices(arr, vertices, indices, tex_n); 

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
	
	add_vertices(arr, vertices, indices, tex_w); 

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
	
	add_vertices(arr, vertices, indices, tex_s); 

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
	
	add_vertices(arr, vertices, indices, tex_e); 

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
	
	add_vertices(arr, vertices, indices, tex_u); 
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
	
	add_vertices(arr, vertices, indices, load_get_texture("dirt_grass_side_01"));

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
	vec3 move_to_pos;
	
	if (bind.state == INPUT_PRESS)
	{
		if (bind.name == "forward")
			move_to_pos = vec3(0.0f, 0.0f, -1.0f);
		if (bind.name == "backward")
			move_to_pos = vec3(0.0f, 0.0f, 1.0f);
		if (bind.name == "left")
			move_to_pos = vec3(-1.0f, 0.0f, 0.0f);		
		if (bind.name == "right")		
			move_to_pos = vec3(1.0f, 0.0f, 0.0f);

		if (move_to_pos.length() > 0)
			player_move_to_tile(pl, tiles, move_to_pos);
	}
}

void player_move_to_tile(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos)
{
	move_to_pos = move_to_pos + pl->ent->trans.position; 

	if (player_can_move_to_tile(pl, tiles, move_to_pos))
	{
		cube *to_tile = tiles[(int)move_to_pos.x][(int)move_to_pos.y][(int)move_to_pos.z];
		
		pl->tile = to_tile;
		pl->ent->trans.position = to_tile->ent->trans.position;
	}
}

bool player_can_move_to_tile(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos)
{
	if (move_to_pos.x < 0 || move_to_pos.y < 0 || move_to_pos.z < 0)
		return false;
	if (move_to_pos.x >= MAX_TILES_X || move_to_pos.y >= MAX_TILES_Y || move_to_pos.z >= MAX_TILES_Z)
		return false;
	
	return tiles[(int)move_to_pos.x][(int)move_to_pos.y][(int)move_to_pos.z] != NULL; 
}
