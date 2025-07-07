#pragma once
#include <SDL3/SDL.h>
#include "mastermind.h"
#include "mastermind_codemaker.h"
#include "mastermind_codebreaker.h"
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

void reset_selected_peg(Peg* peg) {
}

void reset_everything(GameVariables* vars) {
	reset_game(&vars->gameState, &vars->curGuess, vars->guesses, vars->keys);
	generate_random_code(vars->code);
	reset_code_breaker();
	vars->needsRerender = true;
	vars->cursor = 0;
}

