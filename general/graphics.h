#pragma once
#include <SDL3/SDL.h>

void set_color(SDL_Renderer* renderer, const SDL_Color* color);

void render_rect(SDL_Renderer* renderer,
			SDL_FRect* rect, int width,
			const SDL_Color* color, const SDL_Color* borderColor);

void render_circle(SDL_Renderer* renderer,
		float x, float y, float r, float width,
		const SDL_Color* color, const SDL_Color* borderColor);

void render_circle_int(SDL_Renderer* renderer,
		int centreX, int centreY, int radius, int width,
		const SDL_Color* color, const SDL_Color* borderColor);

