#pragma once
#include <math.h>
#include <SDL3/SDL.h>

void set_color(SDL_Renderer* renderer, const SDL_Color* color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
}

void render_rect(SDL_Renderer* renderer,
			SDL_FRect* rect, int width,
			const SDL_Color* color, const SDL_Color* borderColor)
{
	set_color(renderer, borderColor);
	for (int i = 1; i <= width; i++) {
		SDL_FRect borderRect = {rect->x - i, rect->y - i,
								rect->w + 2*i, rect->h + 2*i};
		SDL_RenderRect(renderer, &borderRect);
	}
	set_color(renderer, color);
	SDL_RenderFillRect(renderer, rect);
}

void render_circle(SDL_Renderer* renderer,
		float x, float y, float r, float width,
		const SDL_Color* inside, const SDL_Color* border) {
	// algorithm calculates an octant of circle and mirrors it using this array
	int mirrors[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

	float max_dx, max_dx2, dx, dy, dy2, dx2, px, py, pxm, pym, py2, pxm2, pym2;
	float r2 = r + width;
	max_dx = ceil(sqrt(0.5)*r);
	max_dx2 = ceil(sqrt(0.5)*r2);

	for (dx = 0; dx <= max_dx2; dx++) {
		if (dx < r) {
			dy = sqrt(r * r - dx * dx);
		} else dy = -1;
		dy2 = sqrt(r2 * r2 - dx * dx);
		if (dy2 < r) {
			dx2 = sqrt(r * r - dy2 * dy2);
		} else dx2 = -1;
		
		for (int i = 0; i < 4; i++) {
			px = x + dx * mirrors[i][0];
			py = y + dy * mirrors[i][1];
			pxm = x + dy * mirrors[i][0];
			pym = y + dx * mirrors[i][1];

			py2 = y + dy2 * mirrors[i][1];
			pxm2 = x + dy2 * mirrors[i][0];
			pym2 = y + dx2 * mirrors[i][1];
			// draw inside
			if (dx <= max_dx) {
				set_color(renderer, inside);

				//SDL_RenderPoint(renderer, px, py);
				//SDL_RenderPoint(renderer, pxm, pym);
				SDL_RenderLine(renderer, px, py, px, y);
				SDL_RenderLine(renderer, pxm, pym, pxm, y);

				set_color(renderer, border);
			}
			
			// draw border
			if (width > 0) {
				SDL_RenderLine(renderer, px, py2, px, py);
				SDL_RenderLine(renderer, pxm2, pym, pxm2, pym2);
			}
		}
	}
}

