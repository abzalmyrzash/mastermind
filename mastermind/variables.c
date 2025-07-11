#include "variables.h"
#include "mastermind.h"
#include "codemaker.h"
#include "codebreaker.h"

void reset_everything(GameVariables* vars) {
	reset_game(&vars->gameState, &vars->curGuess, vars->guesses, vars->keys);
	generate_random_code(vars->code);
	reset_code_breaker();
	vars->needsRerender = true;
	vars->cursor = 0;
}

