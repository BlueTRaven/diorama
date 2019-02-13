#pragma once;

#include "gamemath.h"
#include "vertex_handler.h"
#include "gametexture.h"

#include <map>
#include <string>

extern std::map<std::string, texture*> loaded_textures;

struct entity
{
	transform *trans;
	vertex_data *vertices;

	virtual void init(transform *_trans);

	virtual void update(float time);

	virtual void draw();
};

struct cube : entity
{
	bool rotate = false;

	virtual void init(transform *_trans) override;

	virtual void update(float time) override;
};
