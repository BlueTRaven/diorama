#pragma once

#include "gamemath.h"

const static int MAX_TILES_X = 10;
const static int MAX_TILES_Y = 10;
const static int MAX_TILES_Z = 10;

const int DIORAMA_STATE_GAME = 1 << 0;
const int DIORAMA_STATE_EDITOR = 1 << 1;

static int diorama_state;

static vec4 background_color = vec4(1.0f);

static const int WIDTH_DEFAULT = 640;
static const int HEIGHT_DEFAULT = 480;

static int width_current = WIDTH_DEFAULT;
static int height_current = HEIGHT_DEFAULT;

