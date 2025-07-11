#pragma once
#include "definitions.h"
#include "../general/game_state.h"

void check_guess(int* curGuess,
		char guess[CODE_LENGTH],
		char code[CODE_LENGTH],
		char key[CODE_LENGTH],
		GameState* gameState);

void reset_game(GameState* state, int* curGuess,
			char guesses[NUM_GUESSES][CODE_LENGTH],
			char keys[NUM_GUESSES][CODE_LENGTH]);
