#include <stdio.h>
#include <stdlib.h>
#include "mastermind_control.h"

int main() {
	srand(time(NULL));

	SDL_Window* window;
	SDL_Renderer* renderer;
	char* title = "Mastermind";
	SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL;

	SDL_Init(SDL_INIT_VIDEO);
	printf("%s\n", SDL_GetError());
	SDL_CreateWindowAndRenderer(title, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags,
		&window, &renderer);
	printf("%s\n", SDL_GetError());

//	if (SDL_SetRenderVSync(renderer, 1)) {
//		printf("VSync successful!\n");
//	} else {
//		printf("VSync failed!\n");
//	}

//	Uint64 timeStart = SDL_GetTicksNS();
//	for (int i = 0; i < 1000; i++) {
//	render_circle(renderer, 200, 200, 100, 10,
//		&COLOR_RED, &COLOR_BLACK);
//	}
//	Uint64 renderTime = SDL_GetTicksNS() - timeStart;
//	printf("%f\n", renderTime / 1.0e6);
	
	SDL_DisplayID displayID = SDL_GetDisplayForWindow(window);
	const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode(displayID);
	float refreshRate = displayMode->refresh_rate;
	
	printf("Refresh rate: %f\n", refreshRate);
	Uint64 refreshTimeNS = 1e9 / refreshRate;
	printf("Refresh time in nanoseconds: %d\n", refreshTimeNS);

	int curGuess;
	GameState gameState;
	char code[4];
	char guesses[NUM_GUESSES][CODE_LENGTH];
	char keys[NUM_GUESSES][CODE_LENGTH];

	reset_game(&gameState, &curGuess, guesses, keys);
	generate_random_code(code);
	
	init_graphics_variables(guesses);
	Peg *peg = NULL;
	GameVariables gameVars;
	gameVars.gameState = &gameState;
	gameVars.curGuess = &curGuess;
	gameVars.code = &code;
	gameVars.guesses = &guesses;
	gameVars.keys = &keys;
	gameVars.renderer = renderer;
	render_everything(&gameVars, peg);
	char guess_str[4], guess[4], key[4];

	SDL_Event e;
	float mouseX, mouseY;
	int numKeys;
	bool* keyStates;

	Uint64 timeAtStart = SDL_GetTicksNS();
	Uint64 timeElapsed;
	long long timeRemaining;
	int i = 0;

	while (gameState != GAME_QUIT){
		timeAtStart = SDL_GetTicksNS();
	    while (SDL_PollEvent(&e)){
			switch(e.type) 
			{
	        case SDL_EVENT_QUIT:
				gameState = GAME_QUIT;
				break;
	        case SDL_EVENT_KEY_DOWN:
				if (e.key.key == SDLK_ESCAPE) {
					gameState = GAME_QUIT;
				}
				break;
	        case SDL_EVENT_MOUSE_BUTTON_DOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				peg = onClick(&gameVars, mouseX, mouseY);
	        	break;
			case SDL_EVENT_MOUSE_MOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				peg = onMove(&gameVars, peg, mouseX, mouseY);
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				SDL_GetMouseState(&mouseX, &mouseY);
				peg = onRelease(&gameVars, peg, mouseX, mouseY);
				break;
			default:
				break;
			}
	    }
		timeElapsed = SDL_GetTicksNS() - timeAtStart;
		timeRemaining = refreshTimeNS - timeElapsed;
		if (timeRemaining > 0) {
			SDL_DelayNS(timeRemaining);
		} else {
//			printf("%f\n", timeRemaining / 1e6);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
