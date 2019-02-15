#pragma once

#include "gamemath.h"
#include "entity.h"

void camera_init(transform cam_start);

void camera_update(float time);

void camera_start_rotating(int direction);

mat4x4 camera_get_matrix();

struct entity;
void camera_follow_entity(entity *entity);