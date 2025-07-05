#pragma once
#include "mastermind.h"
#include "graphics.h"
#include "button.h"

const SDL_Color background_color = {227, 184, 125, 255};
const SDL_Color peg_border_color = {0, 0, 0, 255};
const SDL_Color board_color = {164,116,73, 255};
const SDL_Color board_border_color = {0, 0, 0, 255};
const SDL_Color selection_box_color = board_color;
const SDL_Color selection_border_color = {0, 0, 0, 255};

const SDL_Color check_button_color = {0, 0, 255, 255};
const SDL_Color check_button_border_color = {0, 0, 0, 255};
const SDL_Color resign_button_color = {255, 255, 255, 255};
const SDL_Color resign_button_border_color = {0, 0, 0, 255};
const SDL_Color reset_button_color = {255, 255, 0, 255};
const SDL_Color reset_button_border_color = {0, 0, 0, 255};
const SDL_Color quit_button_color = {255, 0, 0, 255};
const SDL_Color quit_button_border_color = {0, 0, 0, 255};

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

typedef enum {
	PEG_TYPE_SELECTION,
	PEG_TYPE_HOLE
} PegType;

typedef struct {
	float x, y;
	PegType type;
	char* ptr;
} Peg;

#define NUM_HOLES (NUM_GUESSES * CODE_LENGTH)
#define NUM_CLICKABLE_PEGS (NUM_HOLES + NUM_COLORS)
Peg clickablePegs[NUM_CLICKABLE_PEGS];
char selection[6] = {
	CODE_RED, CODE_GREEN, CODE_BLUE,
	CODE_YELLOW, CODE_WHITE, CODE_BLACK};

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 1200;
float SCALE = 1.0;

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

float correct_peg_offset_y;

float selection_pegs_xy[NUM_COLORS][2];
float code_pegs_xy[NUM_GUESSES][CODE_LENGTH][2];
float key_pegs_xy[NUM_GUESSES][CODE_LENGTH][2];
float correct_pegs_xy[CODE_LENGTH][2];

SDL_FRect check_button_rect;
float check_button_border_width;
Button check_button = { &check_button_rect, &check_button_border_width,
		&check_button_color, &check_button_border_color};

SDL_FRect resign_button_rect;
float resign_button_border_width;
Button resign_button = { &resign_button_rect, &resign_button_border_width,
		&resign_button_color, &resign_button_border_color};

SDL_FRect reset_button_rect;
float reset_button_border_width;
Button reset_button = { &reset_button_rect, &reset_button_border_width,
		&reset_button_color, &reset_button_border_color};

SDL_FRect quit_button_rect;
float quit_button_border_width;
Button quit_button = { &quit_button_rect, &quit_button_border_width,
		&quit_button_color, &quit_button_border_color};

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
	row_offset_y = board_y + 45 * SCALE;
	row_height = 90 * SCALE;

	code_peg_radius = 25 * SCALE;
	code_peg_border_width = 5 * SCALE;
	code_peg_mutual_dist = 90 * SCALE;
	code_peg_offset_x = row_offset_x;
	code_peg_offset_x += code_peg_radius + code_peg_border_width;
 	code_peg_offset_y = row_offset_y;
	code_peg_offset_y += code_peg_radius + code_peg_border_width;

	selection_peg_offset_x = selection_box_x + 30 * SCALE;
	selection_peg_offset_x += code_peg_radius + code_peg_border_width;
	selection_peg_offset_y = selection_box_y + 30 * SCALE;
	selection_peg_offset_y += code_peg_radius + code_peg_border_width;
	
	key_peg_radius = 10 * SCALE;
	key_peg_border_width = 2 * SCALE;
	key_peg_mutual_dist = 30 * SCALE;
	key_peg_offset_x = code_peg_offset_x + code_peg_mutual_dist * 4.5;
	key_peg_offset_x += key_peg_radius + key_peg_border_width;
	key_peg_offset_y = row_offset_y + 3 * SCALE;
	key_peg_offset_y += key_peg_radius + key_peg_border_width;

	correct_peg_offset_y = row_offset_y + 11 * row_height;
	correct_peg_offset_y += code_peg_radius + code_peg_border_width;

	check_button_rect = (SDL_FRect) {
		selection_box_x,
		selection_box_y + selection_box_height + 30 * SCALE,
		90 * SCALE, 90 * SCALE };
	check_button_border_width = 5 * SCALE;

	resign_button_rect = (SDL_FRect) {
		selection_box_x + 120 * SCALE,
		selection_box_y + selection_box_height + 30 * SCALE,
		90 * SCALE, 90 * SCALE };
	resign_button_border_width = 5 * SCALE;

	reset_button_rect = (SDL_FRect) {
		selection_box_x,
		selection_box_y + selection_box_height + 150 * SCALE,
		90 * SCALE, 90 * SCALE };
	reset_button_border_width = 5 * SCALE;

	quit_button_rect = (SDL_FRect) {
		selection_box_x + 120 * SCALE,
		selection_box_y + selection_box_height + 150 * SCALE,
		90 * SCALE, 90 * SCALE };
	quit_button_border_width = 5 * SCALE;

	for (int row = 0; row < NUM_GUESSES; row++) {
		float row_y = row * row_height;

		for (int i = 0; i < CODE_LENGTH; i++) {
			float code_peg_x = code_peg_offset_x + code_peg_mutual_dist * i;
			float code_peg_y = code_peg_offset_y + row_y;

			code_pegs_xy[row][i][0] = code_peg_x;
			code_pegs_xy[row][i][1] = code_peg_y;

			clickablePegs[row * CODE_LENGTH + i].x = code_peg_x;
			clickablePegs[row * CODE_LENGTH + i].y = code_peg_y;

			key_pegs_xy[row][i][0] = key_peg_offset_x
									+ key_peg_mutual_dist * (i % 2);
			key_pegs_xy[row][i][1] = key_peg_offset_y + row_y
									+ key_peg_mutual_dist * (i / 2);
		}
	}

	for (int i = 0; i < NUM_COLORS; i++) {
		float x = selection_peg_offset_x + code_peg_mutual_dist * (i%2);
		float y = selection_peg_offset_y + code_peg_mutual_dist * (i/2);

		selection_pegs_xy[i][0] = x;
		selection_pegs_xy[i][1] = y;

		clickablePegs[NUM_HOLES + i].x = x;
		clickablePegs[NUM_HOLES + i].y = y;
	}
}

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

	calculate_graphics_variables();
}

void render_selection(SDL_Renderer* renderer, Peg* selectedPeg) {
	render_rect(renderer, &selection_box_rect, selection_border_width,
				&selection_box_color, &selection_border_color);

	for (int i = 0; i < 6; i++) {
		if (selectedPeg != NULL &&
			selectedPeg->ptr == &selection[i])
		{
			render_circle(renderer,
				selectedPeg->x, selectedPeg->y,
				code_peg_radius, code_peg_border_width,
				color_map[i], &peg_border_color);
		}
		else {
			render_circle(renderer,
				selection_pegs_xy[i][0], selection_pegs_xy[i][1],
				code_peg_radius, code_peg_border_width,
				color_map[i], &peg_border_color);
		}
	}
}

void render_board(SDL_Renderer* renderer) {
	render_rect(renderer, &board_rect, board_border_width,
				&board_color, &board_border_color);
}

void render_row(SDL_Renderer* renderer, int row,
		char guess[CODE_LENGTH], char key[CODE_LENGTH])
{
	for (int i = 0; i < CODE_LENGTH; i++) {
		render_circle(renderer,
			code_pegs_xy[row][i][0],
			code_pegs_xy[row][i][1],
			code_peg_radius,
			code_peg_border_width,
			color_map[guess[i]],
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

void render_rows(SDL_Renderer* renderer,
		char guesses[NUM_GUESSES][CODE_LENGTH],
		char keys[NUM_GUESSES][CODE_LENGTH]) 
{
	for (int i = 0; i < NUM_GUESSES; i++) {
		render_row(renderer, i, guesses[i], keys[i]);
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

typedef struct {
	GameState* gameState;
	int* curGuess;
	char (*code)[CODE_LENGTH];
	char (*guesses)[NUM_GUESSES][CODE_LENGTH];
	char (*keys)[NUM_GUESSES][CODE_LENGTH];
	SDL_Renderer* renderer;
} GameVariables;

void render_everything(GameVariables* arg, Peg* peg) {
	set_color(arg->renderer, &background_color);
	SDL_RenderClear(arg->renderer);
	
	render_board(arg->renderer);
	render_rows(arg->renderer, *arg->guesses, *arg->keys);
	render_selection(arg->renderer, peg);

	render_button(arg->renderer, &check_button);
	render_button(arg->renderer, &resign_button);
	render_button(arg->renderer, &reset_button);
	render_button(arg->renderer, &quit_button);

	if (*arg->gameState == GAME_WON ||
		*arg->gameState == GAME_LOST)
	{
		render_correct_code(arg->renderer, *arg->code);
	} else {
		
	}
	SDL_RenderPresent(arg->renderer);
}

