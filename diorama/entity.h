#pragma once;

#include "gamemath.h"
#include "vertex_handler.h"

struct entity
{
	vec3 position;
	vec3 scale;
	vec3 rotation;

	virtual void init(entity *e) { }

	virtual void update(entity *e) { }

	virtual void draw(entity *e) { }
};

struct cube : entity
{
	vertex_data *vertex_data;

	virtual void init(entity *e) override;

	virtual void update(entity *e) override;

	virtual	void draw(entity *e) override;	
};
