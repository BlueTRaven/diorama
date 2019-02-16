#pragma once;

#include "gamemath.h"
#include "vertex_handler.h"
#include "gametexture.h"
#include "input.h"
#include "camera.h"

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

	virtual void init(transform _trans);

	virtual void update(float time);

	virtual void draw();

	virtual void on_kill();
};

struct cube : entity
{
	const int SELECTED = 1 << 0;	//first flag

	virtual void init(transform _trans) override;

	virtual void update(float time) override;
};

struct player : entity
{
	keybind_event *kb_event;

	virtual void init(transform _trans) override;

	virtual void update(float time) override;

	virtual void on_kill() override;
};

static void keybind_updated(entity *e, keybind bind);
