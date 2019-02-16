#pragma once

const static int MAX_TILES_X = 10;
const static int MAX_TILES_Y = 10;
const static int MAX_TILES_Z = 10;

const int DIORAMA_STATE_GAME = 1 << 0;
const int DIORAMA_STATE_EDITOR = 1 << 1;

static int diorama_state;
