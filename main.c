#include <time.h>
#include "mastermind_control.h"
#include "button_actions.h"

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

	int curGuess;
	GameState gameState;
	char code[4];
	char guesses[NUM_GUESSES][CODE_LENGTH];
	char keys[NUM_GUESSES][CODE_LENGTH];

	reset_game(&gameState, &curGuess, guesses, keys);
	generate_random_code(code);
	reset_code_breaker();
	
	init_graphics_variables(guesses);
	init_buttons();
	int cursor = 0;

	GameVariables gameVars;
	gameVars.gameState = &gameState;
	gameVars.curGuess = &curGuess;
	gameVars.code = &code;
	gameVars.guesses = &guesses;
	gameVars.keys = &keys;
	gameVars.peg = NULL;
	gameVars.cursor = &cursor;
	gameVars.renderer = renderer;
	gameVars.needsRerender = true;
	render_everything(&gameVars);
	char guess_str[4], guess[4], key[4];

	SDL_Event e;
	float mouseX, mouseY;
	int numKeys;
	bool* keyStates;

	while (gameState != GAME_QUIT){
		SDL_WaitEvent(&e);
		switch(e.type) 
		{
	    case SDL_EVENT_QUIT:
			gameState = GAME_QUIT;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
			calculate_graphics_variables();
			render_everything(&gameVars);
	    case SDL_EVENT_KEY_DOWN:
			onKeyDown(e.key.key, &gameVars);
			break;
	    case SDL_EVENT_MOUSE_BUTTON_DOWN:
			SDL_GetMouseState(&mouseX, &mouseY);
			onClick(mouseX, mouseY, &gameVars);
	    	break;
		case SDL_EVENT_MOUSE_MOTION:
			SDL_GetMouseState(&mouseX, &mouseY);
			onMove(mouseX, mouseY, &gameVars);
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			SDL_GetMouseState(&mouseX, &mouseY);
			onRelease(mouseX, mouseY, &gameVars);
			break;
		default:
			break;
		}
		render_everything(&gameVars);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
