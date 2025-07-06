#pragma once
#include "mastermind_definitions.h"
#include "button.h"
#include <SDL3/SDL.h>

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

SDL_FRect check_button_rect;
float check_button_border_width;
Button check_button = { &check_button_rect,
		&check_button_border_width,
		&check_button_color, &check_button_border_color,
		NULL, BUTTON_NORMAL };

SDL_FRect resign_button_rect;
float resign_button_border_width;
Button resign_button = { &resign_button_rect,
		&resign_button_border_width,
		&resign_button_color, &resign_button_border_color,
		NULL, BUTTON_NORMAL };

SDL_FRect reset_button_rect;
float reset_button_border_width;
Button reset_button = { &reset_button_rect,
		&reset_button_border_width,
		&reset_button_color, &reset_button_border_color,
		NULL, BUTTON_NORMAL };

SDL_FRect quit_button_rect;
float quit_button_border_width;
Button quit_button = { &quit_button_rect, &quit_button_border_width,
		&quit_button_color, &quit_button_border_color,
		NULL, BUTTON_NORMAL };

SDL_FRect random_button_rect;
float random_button_border_width;
Button random_button = { &random_button_rect,
		&random_button_border_width,
		&random_button_color, &random_button_border_color,
		NULL, BUTTON_NORMAL };

SDL_FRect smart_button_rect;
float smart_button_border_width;
Button smart_button = { &smart_button_rect,
		&smart_button_border_width,
		&smart_button_color, &smart_button_border_color,
		NULL, BUTTON_NORMAL };

#define NUM_BUTTONS 6
Button* buttons[NUM_BUTTONS] = {
		&check_button, &resign_button,
		&random_button, &smart_button,
		&reset_button, &quit_button };

