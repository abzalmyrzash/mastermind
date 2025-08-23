#pragma once
#include <SDL3/SDL.h>

typedef enum {
	BUTTON_NORMAL,
	BUTTON_CLICKED,
	BUTTON_RELEASED
} ButtonState;

typedef struct {
	SDL_FRect rect;
	float border_width;
	const SDL_Color* color;
	const SDL_Color* border_color;
	int (*action)(ButtonState* state, void* data);
	ButtonState state;
} Button;

void render_button(SDL_Renderer* renderer, Button* button);

bool try_click_button(float mouseX, float mouseY,
			Button* button, void* data, int* resultPtr);

bool try_release_button(float mouseX, float mouseY,
			Button* button, void* data, int* resultPtr);
