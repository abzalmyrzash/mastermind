#include "mouse_control.h"

bool is_mouse_in_circle(float mouseX, float mouseY,
		float centerX, float centerY, float radius)
{
	float dx = mouseX - centerX;
	float dy = mouseY - centerY;
	return (dx * dx + dy * dy) < radius * radius;
}

bool is_mouse_in_rect(float mouseX, float mouseY, SDL_FRect* rect) {
	return (mouseX > rect->x && mouseX < rect->x + rect->w) &&
		(mouseY > rect->y && mouseY < rect->y + rect->h);
}
