#pragma once
#include "mastermind_graphics.h"
#include "mastermind_codemaker.h"
#include "mastermind_codebreaker.h"
#include "mouse_control.h"

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

	if (*vars->gameState != GAME_ONGOING) return;

	for (int i = 0; i < NUM_CLICKABLE_PEGS; i++) {
		Peg* peg = clickablePegs + i;
		if (is_mouse_in_circle(x, y, peg->x, peg->y, code_peg_radius)) {
			if (peg->type == PEG_TYPE_HOLE) {
				*peg->ptr = CODE_BLANK;
				render_everything(vars);
			}
			vars->peg = peg;
			peg->isClicked = true;
		}
	}

}

void onMove(float x, float y, GameVariables* vars) {
	if (vars->peg == NULL) return;
	if (vars->peg->type == PEG_TYPE_SELECTION && vars->peg->isClicked) {
		vars->peg->x = x;
		vars->peg->y = y;
		render_everything(vars);
	}
}

void onRelease(float x, float y, GameVariables* vars) {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (try_release_button(x, y, buttons[i], vars, NULL)) {
			return;
		}
	}

	if (vars->peg == NULL) return;
	if (vars->peg->type != PEG_TYPE_SELECTION) return;
	bool clickedOnHole = false;
	for (int i = 0; i < NUM_HOLES; i++) {
		int row = i / CODE_LENGTH;
		Peg* peg = clickablePegs + i;
		if (is_mouse_in_circle(x, y, peg->x, peg->y, code_peg_radius)) {
			if (peg->type == PEG_TYPE_HOLE && row == *vars->curGuess) {
				*peg->ptr = *vars->peg->ptr;
				clickedOnHole = true;
			}
			break;
		}
	}
	int i = *vars->peg->ptr;
	vars->peg->x = selection_pegs_xy[i][0];
	vars->peg->y = selection_pegs_xy[i][1];
	vars->peg->isClicked = false;
	render_everything(vars);
}

void onKeyDown(SDL_Keycode key, GameVariables* vars) {
	switch(key)
	{
	case SDLK_ESCAPE:
		*vars->gameState = GAME_QUIT;
		break;
	case SDLK_RETURN:
		check_guess(vars->curGuess,
					(*vars->guesses)[*vars->curGuess],
					*vars->code,
					(*vars->keys)[*vars->curGuess],
					vars->gameState);
		render_everything(vars);
		break;
	case SDLK_BACKSPACE:
		if (--(*vars->cursor) < 0) *vars->cursor = 0;
		(*vars->guesses)[*vars->curGuess][*vars->cursor] = CODE_BLANK;
		render_everything(vars);
		break;
	case SDLK_R:
		make_random_guess(*vars->curGuess, *vars->guesses);
		render_everything(vars);
		break;
	case SDLK_B:
		make_smart_guess(*vars->curGuess, *vars->guesses, *vars->keys);
		render_everything(vars);
		break;
	case SDLK_SPACE:
		reset_everything(vars);
		render_everything(vars);
		break;
	default:
		if (key >= SDLK_0 && key <= SDLK_6) {
			if (*vars->cursor >= CODE_LENGTH) {
				*vars->cursor = 0;
				for (int i = 0; i < CODE_LENGTH; i++) {
					(*vars->guesses)[*vars->curGuess][i] = CODE_BLANK;
				}
			}
			char value = key - SDLK_1;
			if (value < 0) value = CODE_BLANK;
			(*vars->guesses)[*vars->curGuess][*vars->cursor] = value;
			(*vars->cursor)++;
			render_everything(vars);
		}
		break;
	}
}
