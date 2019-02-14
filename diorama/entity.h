#pragma once;

#include "gamemath.h"
#include "vertex_handler.h"
#include "gametexture.h"

#include <map>
#include <string>

extern std::map<std::string, texture*> loaded_textures;

struct entity
{
	transform trans;
	vertex_array *vertices;

	virtual void init(transform _trans);

	virtual void update(float time);

	virtual void draw();
};

struct cube : entity
{
	virtual void init(transform _trans) override;
};
