#pragma once;

#include "gamemath.h"
#include "vertex_handler.h"
#include "gametexture.h"

#include <map>
#include <string>

extern std::map<std::string, texture*> loaded_textures;

struct entity
{
	unsigned int flags;

	transform trans;
	vertex_array *vert_array;

	virtual void init(transform _trans);

	virtual void update(float time);

	virtual void draw();
};

struct cube : entity
{
	const int SELECTED = 1 << 0;	//first flag

	virtual void init(transform _trans) override;

	virtual void update(float time) override;
};
