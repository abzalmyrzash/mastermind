#pragma once
#include "graphics.h"
#include "mouse_control.h"

typedef enum {
	BUTTON_NORMAL,
	BUTTON_CLICKED,
	BUTTON_RELEASED
} ButtonState;

typedef struct {
	SDL_FRect* rect;
	float* border_width;
	const SDL_Color* color;
	const SDL_Color* border_color;
	int (*action)(ButtonState* state, GameVariables* vars);
	ButtonState state;
} Button;

void render_button(SDL_Renderer* renderer, Button* button) {
	render_rect(renderer, button->rect, *button->border_width,
		button->color, button->border_color);
}

bool try_click_button(float mouseX, float mouseY,
			Button* button, GameVariables* vars, int* resultPtr)
{
	if (is_mouse_in_rect(mouseX, mouseY, button->rect)) {
		button->state = BUTTON_CLICKED;
		int result = button->action(&button->state, vars);
		if (resultPtr != NULL)
			*resultPtr = result;
		return true;
	}
}

bool try_release_button(float mouseX, float mouseY,
			Button* button, GameVariables* vars, int* resultPtr)
{
	if (button->state != BUTTON_CLICKED)
		return false;
	if (is_mouse_in_rect(mouseX, mouseY, button->rect)) {
		button->state = BUTTON_RELEASED;
		int result = button->action(&button->state, vars);
		if (resultPtr != NULL)
			*resultPtr = result;
		return true;
	}
}
