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

	camera_follow_entity(pl->ent);		
}

void player_update(player *pl, float time)
{
	pl->ent->trans.origin = pl->ent->trans.position * -1 - vec3(0.5f);
	pl->ent->trans.rotation.y = camera_transform.rotation.y;

	if (pl->is_lerp)
	{
		float percent = (time - pl->lerp_start_time) / PLAYER_LERP_TIME;
		pl->ent->trans.position = vec3_lerp(pl->lerp_start, pl->lerp_end, percent);

		camera_follow_entity(pl->ent);					
		if (percent >= 0.99f)
		{
			pl->ent->trans.position = pl->lerp_end;
			pl->is_lerp = false;
		}
	}
}

void player_keybind_updated(player *pl, float time, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], keybind bind)
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
			player_move_to_tile(pl, time, tiles, move_to_pos);
	}
}

void player_move_to_tile(player *pl, float time, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos)
{
	move_to_pos = move_to_pos + pl->ent->trans.position; 

	int player_can_move = player_can_move_to_tile(pl, tiles, move_to_pos);

	if (player_can_move != PLAYER_CANNOT_MOVE)
	{
		cube *to_tile = NULL;

		if (player_can_move == PLAYER_CAN_MOVE_UP)
			to_tile = tiles[(int)move_to_pos.x][(int)move_to_pos.y + 1][(int)move_to_pos.z]; 
		else if (player_can_move == PLAYER_CAN_MOVE_DOWN)
			to_tile = tiles[(int)move_to_pos.x][(int)move_to_pos.y - 1][(int)move_to_pos.z]; 
		else if (player_can_move == PLAYER_CAN_MOVE)
			to_tile = tiles[(int)move_to_pos.x][(int)move_to_pos.y][(int)move_to_pos.z]; 

		if (to_tile == NULL)
			printf("something went wrong with the walk system.");

		player_begin_lerp(pl, pl->ent->trans.position, to_tile->ent->trans.position, time);

		pl->tile = to_tile;
	}
}

int player_can_move_to_tile(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos)
{
	if (!player_is_valid_tile(tiles, move_to_pos))
		return PLAYER_CANNOT_MOVE;

	cube *tile = tiles[(int)move_to_pos.x][(int)move_to_pos.y][(int)move_to_pos.z];
	if (tile->type == "air")
	{
		int solid_tile = -1;
		std::string solid_tile_type;

		//we can skip i=0 because that's the tile we just looked at - which would have to be air to get here.
		for (int i = 1; i <= 2; i++)
		{
			vec3 pos_down = move_to_pos + vec3(0.0f, i * -1.0f, 0.0f); 

			if (pos_down.y < 0 || pos_down.y >= MAX_TILES_Y)
				break;

			if (player_is_valid_tile(tiles, pos_down))
			{
				cube *tile_dn = tiles[(int)pos_down.x][(int)pos_down.y][(int)pos_down.z];
	
				if (tile_dn->type != "air")
				{
					solid_tile = i;
					solid_tile_type = tile_dn->type;
					break;
				}
			}
		}

		if (solid_tile == -1)
			return PLAYER_CANNOT_MOVE;
		else
		{	//we found a solid tile somewhere down, which means we can move here.
			if (solid_tile == 1)
				return PLAYER_CAN_MOVE;
			else if (solid_tile == 2)
				return PLAYER_CAN_MOVE_DOWN;
			else return PLAYER_CANNOT_MOVE;	//this shouldn't really ever be hit
		}

	}
	else 
	{
		int solid_tile = -1;
		std::string solid_tile_type;

		//the tile we are looking at is solid. Look above it for a non-solid tile.

		vec3 pos_down = move_to_pos + vec3(0.0f, 1.0f, 0.0f); 
		if (player_is_valid_tile(tiles, pos_down))
		{
			cube *tile_new = tiles[(int)pos_down.x][(int)pos_down.y][(int)pos_down.z];
			if (tile_new->type == "air")
				return PLAYER_CAN_MOVE_UP;
			else return PLAYER_CANNOT_MOVE;			
		}
	}
}

bool player_is_valid_tile(cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos)
{
	if (move_to_pos.x < 0 || move_to_pos.y < 0 || move_to_pos.z < 0)
		return false;
	if (move_to_pos.x >= MAX_TILES_X || move_to_pos.y >= MAX_TILES_Y || move_to_pos.z >= MAX_TILES_Z)
		return false;
	
	if (tiles[(int)move_to_pos.x][(int)move_to_pos.y][(int)move_to_pos.z] == NULL)
		return false;

	return true;
}

void player_begin_lerp(player *pl, vec3 start, vec3 end, float time)
{
	pl->lerp_start = start;
	pl->lerp_end = end;

	pl->lerp_start_time = time;

	pl->is_lerp = true;
}
