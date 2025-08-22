#include <stdio.h>
#include "button_actions.h"
#include "mastermind.h"
#include "codemaker.h"
#include "codebreaker.h"
#include "variables.h"
#include "graphics.h"
#include "globals.h"

int check_button_action (ButtonState* buttonState, void* data) {
	GameVariables* vars = (GameVariables*)data;
	if (*buttonState == BUTTON_RELEASED
		&& vars->gameState == GAME_ONGOING)
	{
		check_guess(&vars->curGuess,
					vars->guesses[vars->curGuess],
					vars->code,
					vars->keys[vars->curGuess],
					&vars->gameState);
		vars->cursor = 0;
		vars->needsRerender = true;
		*buttonState = BUTTON_NORMAL;
	}
	return 0;
}

int reset_button_action (ButtonState* buttonState, void* data) {
	GameVariables* vars = (GameVariables*)data;
	if (*buttonState == BUTTON_RELEASED) {
		reset_everything(vars);
		*buttonState = BUTTON_NORMAL;
	}
	return 0;
}

int resign_button_action (ButtonState* buttonState, void* data) {
	GameVariables* vars = (GameVariables*)data;
	if (*buttonState == BUTTON_RELEASED &&
		vars->gameState == GAME_ONGOING)
	{
		printf("YOU RESIGNED!\n");
		vars->gameState = GAME_LOST;
		vars->needsRerender = true;
		*buttonState = BUTTON_NORMAL;
	}
	return 0;
}

int quit_button_action (ButtonState* buttonState, void* data) {
	GameVariables* vars = (GameVariables*)data;
	if (*buttonState == BUTTON_RELEASED) {
		vars->gameState = GAME_QUIT;
	}
	return 0;
}

int random_button_action (ButtonState* buttonState, void* data) {
	GameVariables* vars = (GameVariables*)data;
	if (*buttonState == BUTTON_RELEASED
		&& vars->gameState == GAME_ONGOING)
	{
		make_random_guess(vars->curGuess, vars->guesses);
		vars->cursor = CODE_LENGTH;
		vars->needsRerender = true;
		*buttonState = BUTTON_NORMAL;
	}
	return 0;
}

int smart_button_action (ButtonState* buttonState, void* data) {
	GameVariables* vars = (GameVariables*)data;
	if (*buttonState == BUTTON_RELEASED
		&& vars->gameState == GAME_ONGOING)
	{
		make_smart_guess(vars->curGuess, vars->guesses, vars->keys);
		vars->cursor = CODE_LENGTH;
		vars->needsRerender = true;
		*buttonState = BUTTON_NORMAL;
	}
	return 0;
}

void init_buttons() {
	check_button.action = check_button_action;
	resign_button.action = resign_button_action;
	random_button.action = random_button_action;
	smart_button.action = smart_button_action;
	reset_button.action = reset_button_action;
	quit_button.action = quit_button_action;
}
