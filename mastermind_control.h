#pragma once
#include "mastermind_graphics.h"
#include "mouse_control.h"

bool is_mouse_on_peg(float x, float y, Peg* peg) {
	return is_mouse_in_circle(x, y, peg->x, peg->y,
		code_peg_radius + code_peg_border_width);
}

Peg* onClick(GameVariables* arg, float x, float y) {
	if (is_mouse_on_button(x, y, &quit_button)) {
		*arg->gameState = GAME_QUIT;
		return NULL;
	}

	if (is_mouse_on_button(x, y, &resign_button)) {
		if (*arg->gameState == GAME_ONGOING) {
			*arg->gameState = GAME_LOST;
			render_everything(arg, NULL);
		}
		return NULL;
	}

	if (is_mouse_on_button(x, y, &reset_button)) {
		reset_game(arg->gameState, arg->curGuess, *arg->guesses, *arg->keys);
		generate_random_code(*arg->code);
		render_everything(arg, NULL);
		return NULL;
	}

	if (*arg->gameState != GAME_ONGOING) return NULL;

	if (is_mouse_on_button(x, y, &check_button)) {
		check_guess(arg->curGuess,
					(*arg->guesses)[*arg->curGuess],
					*arg->code,
					(*arg->keys)[*arg->curGuess],
					arg->gameState);
		render_everything(arg, NULL);
		return NULL;
	}

	for (int i = 0; i < NUM_CLICKABLE_PEGS; i++) {
		Peg* peg = clickablePegs + i;
		if (is_mouse_in_circle(x, y, peg->x, peg->y, code_peg_radius)) {
			if (peg->type == PEG_TYPE_HOLE) {
				*peg->ptr = CODE_BLANK;
				render_everything(arg, NULL);
			}
			return peg;
		}
	}

	return NULL;
}

Peg* onMove(GameVariables* arg, Peg* peg, float x, float y) {
	if (peg == NULL) return NULL;
	if (peg->type == PEG_TYPE_SELECTION) {
		peg->x = x;
		peg->y = y;
		render_everything(arg, peg);
	}
	return peg;
}

Peg* onRelease(GameVariables* arg, Peg* selPeg, float x, float y) {
	if (selPeg == NULL) return NULL;
	if (selPeg->type != PEG_TYPE_SELECTION) return NULL;
	bool clickedOnHole = false;
	for (int i = 0; i < NUM_HOLES; i++) {
		int row = i / CODE_LENGTH;
		Peg* peg = clickablePegs + i;
		if (is_mouse_in_circle(x, y, peg->x, peg->y, code_peg_radius)) {
			if (peg->type == PEG_TYPE_HOLE && row == *arg->curGuess) {
				*peg->ptr = *selPeg->ptr;
				clickedOnHole = true;
			}
			break;
		}
	}
	int i = *selPeg->ptr;
	selPeg->x = selection_pegs_xy[i][0];
	selPeg->y = selection_pegs_xy[i][1];
	render_everything(arg, selPeg);
	return NULL;
}
