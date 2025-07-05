#pragma once
#include "graphics.h"
#include "mouse_control.h"

typedef struct {
	SDL_FRect* rect;
	float* border_width;
	const SDL_Color* color;
	const SDL_Color* border_color;
} Button;

void render_button(SDL_Renderer* renderer, Button* button) {
	render_rect(renderer, button->rect, *button->border_width,
		button->color, button->border_color);
}

bool is_mouse_on_button(float mouseX, float mouseY, Button* button) {
	return is_mouse_in_rect(mouseX, mouseY, button->rect);
}
