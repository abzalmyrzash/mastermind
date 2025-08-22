#include "mastermind.h"
#include "control.h"
#include "graphics.h"
#include "codemaker.h"
#include "codebreaker.h"
#include "globals.h"
#include "../general/mouse_control.h"

bool is_mouse_on_peg(float x, float y, Peg* peg) {
	return is_mouse_in_circle(x, y, peg->x, peg->y,
		code_peg_radius + code_peg_border_width);
}

void onClick(float x, float y, GameVariables* vars) {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (try_click_button(x, y, buttons[i], vars, NULL)) {
			return;
		}
	}

	if (vars->gameState != GAME_ONGOING) return;

	for (int i = 0; i < NUM_CLICKABLE_PEGS; i++) {
		Peg* peg = clickablePegs + i;
		if (is_mouse_on_peg(x, y, peg)) {
			vars->peg = peg;
			peg->isClicked = true;
		}
	}
	vars->needsRerender = true;
}

void onMove(float x, float y, GameVariables* vars) {
	if (vars->peg == NULL) return;
	if (vars->peg->isClicked) {
		vars->peg->x = x;
		vars->peg->y = y;
	}
	vars->needsRerender = true;
}

void onRelease(float x, float y, GameVariables* vars) {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (try_release_button(x, y, buttons[i], vars, NULL)) {
			return;
		}
	}

	if (vars->peg == NULL) return;

	int i = *vars->peg->ptr;
	vars->peg->x = vars->peg->xOrig;
	vars->peg->y = vars->peg->yOrig;
	vars->peg->isClicked = false;

	bool clickedOnHole = false;
	for (int i = 0; i < NUM_HOLES; i++) {
		int row = i / CODE_LENGTH;
		Peg* peg = clickablePegs + i;
		if (is_mouse_on_peg(x, y, peg)) {
			if (peg->type == PEG_TYPE_HOLE && row == vars->curGuess) {
				if (vars->peg->type == PEG_TYPE_HOLE) {
					swap_peg_values(peg, vars->peg);
				}
				else {
					*peg->ptr = *vars->peg->ptr;
				}
				clickedOnHole = true;
			}
			break;
		}
	}
	if (!clickedOnHole) {
		if (vars->peg->type == PEG_TYPE_HOLE) {
			*vars->peg->ptr = CODE_BLANK;
		}
	}
	vars->needsRerender = true;
}

void onKeyDown(SDL_Keycode key, GameVariables* vars) {
	switch(key)
	{
	case SDLK_ESCAPE:
		vars->gameState = GAME_QUIT;
		break;
	case SDLK_SPACE:
		reset_everything(vars);
		vars->needsRerender = true;
		break;
	default:
		break;
	}
	if (vars->gameState != GAME_ONGOING) return;
	switch(key)
	{
	case SDLK_RETURN:
		check_guess(&vars->curGuess,
					vars->guesses[vars->curGuess],
					vars->code,
					vars->keys[vars->curGuess],
					&vars->gameState);
		vars->needsRerender = true;
		vars->cursor = 0;
		break;
	case SDLK_R:
		make_random_guess(vars->curGuess, vars->guesses);
		vars->needsRerender = true;
		vars->cursor = CODE_LENGTH;
		break;
	case SDLK_B:
		make_smart_guess(vars->curGuess, vars->guesses, vars->keys);
		vars->needsRerender = true;
		vars->cursor = CODE_LENGTH;
		break;
	case SDLK_L:
		vars->gameState = GAME_LOST;
		vars->needsRerender = true;
		break;
	case SDLK_DELETE:
		for (int i = 0; i < CODE_LENGTH; i++) {
			(vars->guesses)[vars->curGuess][i] = CODE_BLANK;
		}
		vars->cursor = 0;
		vars->needsRerender = true;
		break;
	case SDLK_BACKSPACE:
		if (--(vars->cursor) < 0) vars->cursor = 0;
		vars->guesses[vars->curGuess][vars->cursor] = CODE_BLANK;
		vars->needsRerender = true;
		break;
	default:
		if (key >= SDLK_0 && key <= SDLK_6) {
			if (vars->cursor >= CODE_LENGTH) {
				vars->cursor = 0;
				for (int i = 0; i < CODE_LENGTH; i++) {
					(vars->guesses)[vars->curGuess][i] = CODE_BLANK;
				}
			}
			char value = key - SDLK_1;
			if (value < 0) value = CODE_BLANK;
			vars->guesses[vars->curGuess][vars->cursor] = value;
			(vars->cursor)++;
		}
		vars->needsRerender = true;
		break;
	}
}
