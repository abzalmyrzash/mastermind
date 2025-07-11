#ifndef MASTERMIND_GLOBALS_H
#define MASTERMIND_GLOBALS_H
#include <SDL3/SDL.h>
#include "../general/button.h"
#include "definitions.h"
#include "peg.h"

#define NUM_HOLES (NUM_GUESSES * CODE_LENGTH)
#define NUM_CLICKABLE_PEGS (NUM_HOLES + NUM_COLORS)

extern const SDL_Color background_color;
extern const SDL_Color peg_border_color;
extern const SDL_Color board_color;
extern const SDL_Color board_border_color;
extern const SDL_Color selection_box_color;
extern const SDL_Color selection_border_color;

extern const SDL_Color check_button_color;
extern const SDL_Color check_button_border_color;
extern const SDL_Color resign_button_color;
extern const SDL_Color resign_button_border_color;
extern const SDL_Color reset_button_color;
extern const SDL_Color reset_button_border_color;
extern const SDL_Color quit_button_color;
extern const SDL_Color quit_button_border_color;
extern const SDL_Color random_button_color;
extern const SDL_Color random_button_border_color;
extern const SDL_Color smart_button_color;
extern const SDL_Color smart_button_border_color;

extern const SDL_Color COLOR_RED;
extern const SDL_Color COLOR_GREEN;
extern const SDL_Color COLOR_BLUE;
extern const SDL_Color COLOR_YELLOW;
extern const SDL_Color COLOR_WHITE;
extern const SDL_Color COLOR_BLACK;
extern const SDL_Color COLOR_BLANK;

extern const SDL_Color* color_map[];

extern Peg clickablePegs[NUM_CLICKABLE_PEGS];
extern char selection[6];

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float SCALE;

extern SDL_FRect board_rect;
extern float board_x;
extern float board_y;
extern float board_width;
extern float board_height;
extern float board_border_width;

extern SDL_FRect selection_box_rect;
extern float selection_box_x;
extern float selection_box_y;
extern float selection_box_width;
extern float selection_box_height;
extern float selection_border_width;

extern float row_height;
extern float row_offset_x;
extern float row_offset_y;

extern float code_peg_radius;
extern float code_peg_border_width;
extern float code_peg_mutual_dist;
extern float code_peg_offset_x;
extern float code_peg_offset_y;

extern float selection_peg_offset_x;
extern float selection_peg_offset_y;

extern float key_peg_radius;
extern float key_peg_border_width;
extern float key_peg_mutual_dist;
extern float key_peg_offset_x;
extern float key_peg_offset_y;

extern float row_peg_radius;
extern float row_peg_border_width;
extern float row_peg_offset_x;
extern float row_peg_offset_y;

extern float correct_peg_offset_y;

extern float code_pegs_xy[NUM_GUESSES][CODE_LENGTH][2];
extern float key_pegs_xy[NUM_GUESSES][CODE_LENGTH][2];
extern float row_pegs_xy[NUM_GUESSES][2];
extern float correct_pegs_xy[CODE_LENGTH][2];
extern float selection_pegs_xy[NUM_COLORS][2];

extern SDL_FRect check_button_rect;
extern float check_button_border_width;
extern Button check_button;

extern SDL_FRect resign_button_rect;
extern float resign_button_border_width;
extern Button resign_button;

extern SDL_FRect reset_button_rect;
extern float reset_button_border_width;
extern Button reset_button;

extern SDL_FRect quit_button_rect;
extern float quit_button_border_width;
extern Button quit_button;

extern SDL_FRect random_button_rect;
extern float random_button_border_width;
extern Button random_button;

extern SDL_FRect smart_button_rect;
extern float smart_button_border_width;
extern Button smart_button;

#define NUM_BUTTONS 6
extern Button* buttons[NUM_BUTTONS];

#endif
