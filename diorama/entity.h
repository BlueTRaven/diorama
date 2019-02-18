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

const int PLAYER_CANNOT_MOVE = 0;
const int PLAYER_CAN_MOVE_UP = 1;
const int PLAYER_CAN_MOVE_DOWN = 2;
const int PLAYER_CAN_MOVE = 3;

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

	std::string type;
};

void cube_init(entity *ent, cube *c, Decl cube_asset);

void cube_update(cube *c, float time);

const float PLAYER_LERP_TIME = 0.25f; //1/4th of a second to lerp

struct player
{
	entity *ent;
	keybind_event *kb_event;

	cube *tile;

	float lerp_start_time;
	bool is_lerp;
	vec3 lerp_start;
	vec3 lerp_end;

	bool is_lerp_queued;
	vec3 lerp_queued_end;
};

void player_init(entity *ent, player *pl);

void player_update(player *pl, float time);

void player_keybind_updated(player *pl, float time, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], keybind bind);

void player_move_to_tile(player *pl, float time, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos);

int player_can_move_to_tile(player *pl, cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos);

bool player_is_valid_tile(cube *tiles[MAX_TILES_X][MAX_TILES_Y][MAX_TILES_Z], vec3 move_to_pos);

void player_begin_lerp(player *pl, vec3 start, vec3 end, float time);
