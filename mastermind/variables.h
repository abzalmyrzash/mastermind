#pragma once
#include <SDL3/SDL.h>
#include "../general/game_state.h"
#include "definitions.h"
#include "peg.h"

typedef struct {
	GameState gameState;
	int curGuess;
	char code[CODE_LENGTH];
	char guesses[NUM_GUESSES][CODE_LENGTH];
	char keys[NUM_GUESSES][CODE_LENGTH];
	Peg* peg;
	int cursor;
	SDL_Renderer* renderer;
	bool needsRerender;
} GameVariables;

void reset_everything(GameVariables* vars);
