#pragma once;

#include "gamemath.h"
#include "vertex_handler.h"
#include "gametexture.h"
#include "input.h"
#include "camera.h"
#include "game.h"

#include <map>
#include <string>

extern std::map<std::string, texture*> loaded_textures;

extern transform camera_transform;

struct entity
{
	const unsigned int DEAD = 1 << 31;

	unsigned int flags;

	unsigned int debug_flags;
	unsigned int editor_flags;

	transform trans;
	vertex_array *vert_array;

};

void entity_init(entity *ent, transform _trans);

void entity_draw(entity *ent);

const int CUBE_SELECTED = 1 << 0;
struct cube
{
	entity *ent;
};

void cube_init(entity *ent, cube *c);

void cube_update(cube *c, float time);

struct player
{
	entity *ent;
	keybind_event *kb_event;

	cube *tile;
};

void player_init(entity *ent, player *pl);

void player_update(player *pl, float time);

void player_keybind_updated(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], keybind bind);

void player_can_move_to_tile(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], cube *to_tile);

