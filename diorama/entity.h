#pragma once;

#include "gamemath.h"
#include "vertex_handler.h"

struct entity
{
	transform *trans;
	vertex_data *vertices;

	virtual void init();

	virtual void update();

	virtual void draw();
};

struct cube : entity
{
	bool rotate = false;

	virtual void init() override;

	virtual void update() override;

	virtual	void draw() override;	
};
