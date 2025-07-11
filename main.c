#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include "mastermind/globals.h"
#include "mastermind/graphics.h"
#include "mastermind/control.h"
#include "mastermind/button_actions.h"

int main() {
	srand(time(NULL));

	SDL_Window* window;
	SDL_Renderer* renderer;
	char* title = "Mastermind";
	SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Init(SDL_INIT_VIDEO);
	printf("%s\n", SDL_GetError());
	SDL_CreateWindowAndRenderer(title, SCREEN_WIDTH, SCREEN_HEIGHT,
		windowFlags, &window, &renderer);
	printf("%s\n", SDL_GetError());

	GameVariables vars;
	vars.renderer = renderer;
	vars.peg = NULL;

	reset_everything(&vars);
	
	init_graphics_variables(vars.guesses);
	init_buttons();

	render_everything(&vars);

	SDL_Event e;
	float mouseX, mouseY;
	int numKeys;
	bool* keyStates;

	while (vars.gameState != GAME_QUIT){
		SDL_WaitEvent(&e);
		switch(e.type) 
		{
	    case SDL_EVENT_QUIT:
			vars.gameState = GAME_QUIT;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
			calculate_graphics_variables();
			render_everything(&vars);
	    case SDL_EVENT_KEY_DOWN:
			onKeyDown(e.key.key, &vars);
			break;
	    case SDL_EVENT_MOUSE_BUTTON_DOWN:
			SDL_GetMouseState(&mouseX, &mouseY);
			onClick(mouseX, mouseY, &vars);
	    	break;
		case SDL_EVENT_MOUSE_MOTION:
			SDL_GetMouseState(&mouseX, &mouseY);
			onMove(mouseX, mouseY, &vars);
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			SDL_GetMouseState(&mouseX, &mouseY);
			onRelease(mouseX, mouseY, &vars);
			break;
		default:
			break;
		}
		render_everything(&vars);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
