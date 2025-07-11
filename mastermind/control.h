#pragma once
#include <stdbool.h>
#include "variables.h"
#include <SDL3/SDL.h>

bool is_mouse_on_peg(float x, float y, Peg* peg);

void onClick(float x, float y, GameVariables* vars);

void onMove(float x, float y, GameVariables* vars);

void onRelease(float x, float y, GameVariables* vars);

void onKeyDown(SDL_Keycode key, GameVariables* vars);
