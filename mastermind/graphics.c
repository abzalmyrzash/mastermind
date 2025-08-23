#include "graphics.h"
#include "globals.h"
#include "../general/graphics.h"

const SDL_Color background_color = {227, 184, 125, 255};
const SDL_Color peg_border_color = {0, 0, 0, 255};
const SDL_Color board_color = {164,116,73, 255};
const SDL_Color board_border_color = {0, 0, 0, 255};
const SDL_Color selection_box_color = board_color;
const SDL_Color selection_border_color = {0, 0, 0, 255};

const SDL_Color check_button_color = {0, 255, 0, 255};
const SDL_Color check_button_border_color = {0, 0, 0, 255};
const SDL_Color resign_button_color = {255, 255, 255, 255};
const SDL_Color resign_button_border_color = {0, 0, 0, 255};
const SDL_Color reset_button_color = {255, 255, 0, 255};
const SDL_Color reset_button_border_color = {0, 0, 0, 255};
const SDL_Color quit_button_color = {255, 0, 0, 255};
const SDL_Color quit_button_border_color = {0, 0, 0, 255};
const SDL_Color random_button_color = {255, 0, 255, 255};
const SDL_Color random_button_border_color = {0, 0, 0, 255};
const SDL_Color smart_button_color = {0, 0, 255, 255};
const SDL_Color smart_button_border_color = {0, 0, 0, 255};

const SDL_Color COLOR_RED = {255, 0, 0, 255};
const SDL_Color COLOR_GREEN = {0, 255, 0, 255};
const SDL_Color COLOR_BLUE = {0, 0, 255, 255};
const SDL_Color COLOR_YELLOW = {255, 255, 0, 255};
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
const SDL_Color COLOR_BLANK = {150,108,68, 255};

const SDL_Color* color_map[] = {
	&COLOR_RED, &COLOR_GREEN, &COLOR_BLUE,
	&COLOR_YELLOW, &COLOR_WHITE, &COLOR_BLACK, &COLOR_BLANK
};

SDL_FRect board_rect;
float board_x;
float board_y;
float board_width;
float board_height;
float board_border_width;

SDL_FRect selection_box_rect;
float selection_box_x;
float selection_box_y;
float selection_box_width;
float selection_box_height;
float selection_border_width;

float row_height;
float row_offset_x;
float row_offset_y;

float code_peg_radius;
float code_peg_border_width;
float code_peg_mutual_dist;
float code_peg_offset_x;
float code_peg_offset_y;

float selection_peg_offset_x;
float selection_peg_offset_y;

float key_peg_radius;
float key_peg_border_width;
float key_peg_mutual_dist;
float key_peg_offset_x;
float key_peg_offset_y;

float row_peg_radius;
float row_peg_border_width;
float row_peg_offset_x;
float row_peg_offset_y;

float correct_peg_offset_y;

float code_pegs_xy[NUM_GUESSES][CODE_LENGTH][2];
float key_pegs_xy[NUM_GUESSES][CODE_LENGTH][2];
float row_pegs_xy[NUM_GUESSES][2];
float correct_pegs_xy[CODE_LENGTH][2];
float selection_pegs_xy[NUM_COLORS][2];

char selection[6] = {
	CODE_RED, CODE_GREEN, CODE_BLUE,
	CODE_YELLOW, CODE_WHITE, CODE_BLACK};

Button check_button, resign_button, random_button, smart_button, reset_button, quit_button;

SDL_FRect check_button_rect;
float check_button_border_width;

SDL_FRect resign_button_rect;
float resign_button_border_width;

SDL_FRect reset_button_rect;
float reset_button_border_width;

SDL_FRect quit_button_rect;
float quit_button_border_width;

SDL_FRect random_button_rect;
float random_button_border_width;

SDL_FRect smart_button_rect;
float smart_button_border_width;

void init_graphics_variables(char guesses[NUM_GUESSES][CODE_LENGTH]) {
	for (int row = 0; row < NUM_GUESSES; row++) {
		for (int i = 0; i < CODE_LENGTH; i++) {
			clickablePegs[row * CODE_LENGTH + i].type = PEG_TYPE_HOLE;
			clickablePegs[row * CODE_LENGTH + i].ptr = &guesses[row][i];
		}
	}
	for (int i = 0; i < NUM_COLORS; i++) {
		clickablePegs[NUM_HOLES + i].type = PEG_TYPE_SELECTION;
		clickablePegs[NUM_HOLES + i].ptr = &selection[i];
	}
	check_button.color = &check_button_color;
	check_button.border_color = &check_button_border_color;

	resign_button.color = &resign_button_color;
	resign_button.border_color = &resign_button_border_color;

	random_button.color = &random_button_color;
	random_button.border_color = &random_button_border_color;

	smart_button.color = &smart_button_color;
	smart_button.border_color = &smart_button_border_color;

	reset_button.color = &reset_button_color;
	reset_button.border_color = &reset_button_border_color;

	quit_button.color = &quit_button_color;
	quit_button.border_color = &quit_button_border_color;

	calculate_graphics_variables();
}

void calculate_graphics_variables() {
	board_width = 600 * SCALE;
	board_height = 1150 * SCALE;
	board_x = (SCREEN_WIDTH - board_width) / 2 * SCALE;
	board_y = (SCREEN_HEIGHT - board_height) / 2 * SCALE;

	board_rect = (SDL_FRect) { board_x, board_y, board_width, board_height };
	board_border_width = 5 * SCALE;

	selection_box_width = 210 * SCALE;
	selection_box_height = 300 * SCALE;
	selection_box_x = 45 * SCALE;
	selection_box_y = board_y;
	
	selection_box_rect = (SDL_FRect) {
		selection_box_x, selection_box_y,
		selection_box_width, selection_box_height
	};
	selection_border_width = 5 * SCALE;
	
	row_offset_x = board_x + 60 * SCALE;
	row_offset_y = board_y + 60 * SCALE;
	row_height = 90 * SCALE;

	code_peg_radius = 25 * SCALE;
	code_peg_border_width = 5 * SCALE;
	code_peg_mutual_dist = 80 * SCALE;
	code_peg_offset_x = row_offset_x + code_peg_mutual_dist;
 	code_peg_offset_y = row_offset_y;

	selection_peg_offset_x = selection_box_x + 60 * SCALE;
	selection_peg_offset_y = selection_box_y + 60 * SCALE;
	
	key_peg_radius = 10 * SCALE;
	key_peg_border_width = 2 * SCALE;
	key_peg_mutual_dist = 30 * SCALE;
	key_peg_offset_x = code_peg_offset_x + code_peg_mutual_dist * 4.5;
	key_peg_offset_y = row_offset_y - key_peg_mutual_dist / 2;

	row_peg_radius = key_peg_radius;
	row_peg_border_width = 2 * SCALE;
	row_peg_offset_x = row_offset_x;
	row_peg_offset_y = row_offset_y;

	correct_peg_offset_y = row_offset_y + 10.5 * row_height;
	correct_peg_offset_y += code_peg_radius + code_peg_border_width;

	check_button.rect = (SDL_FRect) {
		selection_box_x,
		selection_box_y + selection_box_height + 30 * SCALE,
		90 * SCALE, 90 * SCALE };
	check_button.border_width = 5 * SCALE;

	resign_button.rect = (SDL_FRect) {
		selection_box_x + 120 * SCALE,
		selection_box_y + selection_box_height + 30 * SCALE,
		90 * SCALE, 90 * SCALE };
	resign_button.border_width = 5 * SCALE;

	random_button.rect = (SDL_FRect) {
		selection_box_x,
		selection_box_y + selection_box_height + 150 * SCALE,
		90 * SCALE, 90 * SCALE };
	random_button.border_width = 5 * SCALE;

	smart_button.rect = (SDL_FRect) {
		selection_box_x + 120 * SCALE,
		selection_box_y + selection_box_height + 150 * SCALE,
		90 * SCALE, 90 * SCALE };
	smart_button.border_width = 5 * SCALE;

	reset_button.rect = (SDL_FRect) {
		selection_box_x,
		selection_box_y + selection_box_height + 270 * SCALE,
		90 * SCALE, 90 * SCALE };
	reset_button.border_width = 5 * SCALE;

	quit_button.rect = (SDL_FRect) {
		selection_box_x + 120 * SCALE,
		selection_box_y + selection_box_height + 270 * SCALE,
		90 * SCALE, 90 * SCALE };
	quit_button.border_width = 5 * SCALE;

	for (int row = 0; row < NUM_GUESSES; row++) {
		float row_y = row * row_height;

		for (int i = 0; i < CODE_LENGTH; i++) {
			float code_peg_x = code_peg_offset_x + code_peg_mutual_dist * i;
			float code_peg_y = code_peg_offset_y + row_y;

			code_pegs_xy[row][i][0] = code_peg_x;
			code_pegs_xy[row][i][1] = code_peg_y;

			clickablePegs[row * CODE_LENGTH + i].x = code_peg_x;
			clickablePegs[row * CODE_LENGTH + i].y = code_peg_y;
			clickablePegs[row * CODE_LENGTH + i].xOrig = code_peg_x;
			clickablePegs[row * CODE_LENGTH + i].yOrig = code_peg_y;

			key_pegs_xy[row][i][0] = key_peg_offset_x
									+ key_peg_mutual_dist * (i % 2);
			key_pegs_xy[row][i][1] = key_peg_offset_y + row_y
									+ key_peg_mutual_dist * (i / 2);
		}
		row_pegs_xy[row][0] = row_peg_offset_x;
		row_pegs_xy[row][1] = row_peg_offset_y + row_y;
	}

	for (int i = 0; i < NUM_COLORS; i++) {
		float x = selection_peg_offset_x + code_peg_mutual_dist * (i%2);
		float y = selection_peg_offset_y + code_peg_mutual_dist * (i/2);

		selection_pegs_xy[i][0] = x;
		selection_pegs_xy[i][1] = y;

		clickablePegs[NUM_HOLES + i].x = x;
		clickablePegs[NUM_HOLES + i].y = y;
		clickablePegs[NUM_HOLES + i].xOrig = x;
		clickablePegs[NUM_HOLES + i].yOrig = y;
	}
}

void render_selection(SDL_Renderer* renderer, Peg* selectedPeg) {
	render_rect(renderer, &selection_box_rect, selection_border_width,
				&selection_box_color, &selection_border_color);

	for (int i = 0; i < 6; i++) {
		if (selectedPeg == NULL ||
			selectedPeg->ptr != &selection[i])
		{
			render_circle(renderer,
				selection_pegs_xy[i][0], selection_pegs_xy[i][1],
				code_peg_radius, code_peg_border_width,
				color_map[i], &peg_border_color);
		}
	}
}

void render_selected_peg(SDL_Renderer* renderer, Peg* peg) {
	if (peg != NULL) {
		render_circle(renderer,
			peg->x, peg->y,
			code_peg_radius, code_peg_border_width,
			color_map[*peg->ptr], &peg_border_color);
	}
}

void render_board(SDL_Renderer* renderer) {
	render_rect(renderer, &board_rect, board_border_width,
				&board_color, &board_border_color);
}

void render_row(SDL_Renderer* renderer, int row, int curGuess,
		char guess[CODE_LENGTH], char key[CODE_LENGTH], Peg* selectedPeg)
{
	const SDL_Color* row_peg_color = &COLOR_BLANK;
	if (row == curGuess) row_peg_color = &COLOR_WHITE;
	render_circle(renderer,
		row_pegs_xy[row][0],
		row_pegs_xy[row][1],
		row_peg_radius,
		row_peg_border_width,
		row_peg_color,
		&peg_border_color);

	for (int i = 0; i < CODE_LENGTH; i++) {
		const SDL_Color* color = color_map[guess[i]];
		if (selectedPeg != NULL && selectedPeg->ptr == &guess[i])
			color = &COLOR_BLANK;
		render_circle(renderer,
			code_pegs_xy[row][i][0],
			code_pegs_xy[row][i][1],
			code_peg_radius,
			code_peg_border_width,
			color,
			&peg_border_color);
	}

	for (int i = 0; i < CODE_LENGTH; i++) {
		render_circle(renderer,
			key_pegs_xy[row][i][0],
			key_pegs_xy[row][i][1],
			key_peg_radius,
			key_peg_border_width,
			color_map[key[i]],
			&peg_border_color);
	}
}

void render_rows(SDL_Renderer* renderer, int curGuess,
		char guesses[NUM_GUESSES][CODE_LENGTH],
		char keys[NUM_GUESSES][CODE_LENGTH], Peg* selectedPeg) 
{
	for (int i = 0; i < NUM_GUESSES; i++) {
		render_row(renderer, i, curGuess, guesses[i], keys[i], selectedPeg);
	}
}

void render_correct_code(SDL_Renderer* renderer, char code[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) {
		render_circle(renderer,
			code_peg_offset_x + code_peg_mutual_dist * i,
			correct_peg_offset_y,
			code_peg_radius,
			code_peg_border_width,
			color_map[code[i]],
			&peg_border_color);
	}
}

void render_everything(GameVariables* vars) {
	if (!vars->needsRerender) return;
	set_color(vars->renderer, &background_color);
	SDL_RenderClear(vars->renderer);
	
	render_board(vars->renderer);
	render_rows(vars->renderer, vars->curGuess, vars->guesses, vars->keys, vars->peg);
	render_selection(vars->renderer, vars->peg);

	for (int i = 0; i < NUM_BUTTONS; i++) {
		render_button(vars->renderer, buttons[i]);
	}

	render_selected_peg(vars->renderer, vars->peg);

	if (vars->gameState == GAME_WON ||
		vars->gameState == GAME_LOST)
	{
		render_correct_code(vars->renderer, vars->code);
	} else {
		
	}
	SDL_RenderPresent(vars->renderer);
	vars->needsRerender = false;
}

