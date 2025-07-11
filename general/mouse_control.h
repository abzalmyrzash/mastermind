#pragma once
#include "SDL3/SDL.h"

bool is_mouse_in_circle(float mouseX, float mouseY,
		float centerX, float centerY, float radius);

bool is_mouse_in_rect(float mouseX, float mouseY, SDL_FRect* rect);
