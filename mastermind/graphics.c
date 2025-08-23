#include "graphics.h"
#include "globals.h"
#include "stdio.h"
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
	&COLOR_RED, &COLOR_BLUE, &COLOR_GREEN,
	&COLOR_YELLOW, &COLOR_WHITE, &COLOR_BLACK, &COLOR_BLANK
};

const SDL_Color* key_color_map[] = {
	&COLOR_RED, &COLOR_WHITE, &COLOR_BLANK
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
float code_peg_full_radius;
float code_peg_w;
float code_peg_mutual_dist;
float code_peg_offset_x;
float code_peg_offset_y;

float selection_peg_offset_x;
float selection_peg_offset_y;

float key_peg_radius;
float key_peg_border_width;
float key_peg_full_radius;
float key_peg_w;
float key_peg_mutual_dist;
float key_peg_offset_x;
float key_peg_offset_y;

float row_peg_radius;
float row_peg_border_width;
float row_peg_offset_x;
float row_peg_offset_y;

float correct_peg_offset_y;

SDL_FRect selection_pegs_rect[NUM_COLORS];
SDL_FRect row_pegs_rect[NUM_GUESSES];
SDL_FRect code_pegs_rect[NUM_GUESSES][CODE_LENGTH];
SDL_FRect key_pegs_rect[NUM_GUESSES][CODE_LENGTH];
SDL_FRect correct_pegs_rect[CODE_LENGTH];
SDL_FRect selected_peg_rect;

char selection[NUM_COLORS] = {
	CODE_RED, CODE_BLUE, CODE_GREEN,
	CODE_YELLOW, CODE_WHITE, CODE_BLACK};

Button check_button, resign_button, random_button, smart_button, reset_button, quit_button;

float button_width, button_height, button_border_width;

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

SDL_Texture* board_texture;
SDL_Texture* selection_box_texture;
SDL_Texture* code_peg_textures[NUM_WITH_BLANK];
SDL_Texture* key_peg_textures[3];
SDL_Texture* button_textures[NUM_BUTTONS];

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

void create_textures(SDL_Renderer* renderer) {
	for (int i = 0; i < NUM_WITH_BLANK; i++) {
		code_peg_textures[i] = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, code_peg_w, code_peg_w);
		SDL_SetRenderTarget(renderer, code_peg_textures[i]);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		render_circle(renderer,
			code_peg_full_radius, code_peg_full_radius,
			code_peg_radius, code_peg_border_width,
			color_map[i], &peg_border_color);
	}

	for (int i = 0; i < 3; i++) {
		key_peg_textures[i] = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, key_peg_w, key_peg_w);
		SDL_SetRenderTarget(renderer, key_peg_textures[i]);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		render_circle(renderer,
			key_peg_full_radius, key_peg_full_radius,
			key_peg_radius, key_peg_border_width,
			key_color_map[i], &peg_border_color);
	}

	SDL_FRect rect;
	board_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
		board_width,
		board_height);
	SDL_SetRenderTarget(renderer, board_texture);
	rect = board_rect;
	rect.x = 0; rect.y = 0;
	render_rect(renderer, &rect, board_border_width,
				&board_color, &board_border_color);

	selection_box_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
		selection_box_width,
		selection_box_height);
	SDL_SetRenderTarget(renderer, selection_box_texture);
	rect = selection_box_rect;
	rect.x = 0; rect.y = 0;
	render_rect(renderer, &rect, selection_border_width,
				&selection_box_color, &selection_border_color);

	for (int i = 0; i < NUM_BUTTONS; i++) {
		button_textures[i] = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
			button_width,
			button_height);
		SDL_SetRenderTarget(renderer, button_textures[i]);
		float x = buttons[i]->rect.x;
		float y = buttons[i]->rect.y;
		buttons[i]->rect.x = 0;
		buttons[i]->rect.y = 0;
		render_button(renderer, buttons[i]);
		buttons[i]->rect.x = x;
		buttons[i]->rect.y = y;
	}
	SDL_SetRenderTarget(renderer, NULL);
}

void destroy_textures() {
	for (int i = 0; i < NUM_COLORS; i++) {
		SDL_DestroyTexture(code_peg_textures[i]);
	}
	for (int i = 0; i < 3; i++) {
		SDL_DestroyTexture(key_peg_textures[i]);
	}
	SDL_DestroyTexture(board_texture);
	SDL_DestroyTexture(selection_box_texture);
	SDL_DestroyTexture(board_texture);
	for (int i = 0; i < NUM_BUTTONS; i++) {
		SDL_DestroyTexture(button_textures[i]);
	}
}

void calculate_graphics_variables() {
	board_width = 600 * SCALE;
	board_height = 1150 * SCALE;
	board_x = (SCREEN_WIDTH - board_width) / 2 * SCALE;
	board_y = (SCREEN_HEIGHT - board_height) / 2 * SCALE;
	board_border_width = 5 * SCALE;
	board_rect = (SDL_FRect) { board_x, board_y,
		board_width, board_height };

	selection_box_width = 210 * SCALE;
	selection_box_height = 290 * SCALE;
	selection_box_x = 50 * SCALE;
	selection_box_y = board_y;
	
	selection_box_rect = (SDL_FRect) {
		selection_box_x, selection_box_y,
		selection_box_width, selection_box_height
	};
	selection_border_width = 5 * SCALE;
	
	row_offset_x = board_x + board_border_width + 60 * SCALE;
	row_offset_y = board_y + board_border_width + 60 * SCALE;
	row_height = 90 * SCALE;

	code_peg_radius = 25 * SCALE;
	code_peg_border_width = 5 * SCALE;
	code_peg_mutual_dist = 80 * SCALE;
	code_peg_offset_x = row_offset_x + code_peg_mutual_dist;
 	code_peg_offset_y = row_offset_y;
	code_peg_full_radius = code_peg_radius + code_peg_border_width;
	code_peg_w = code_peg_full_radius * 2 + 1;

	selection_peg_offset_x = selection_box_x + selection_border_width + 60 * SCALE;
	selection_peg_offset_y = selection_box_y + selection_border_width + 60 * SCALE;
	
	key_peg_radius = 10 * SCALE;
	key_peg_border_width = 2 * SCALE;
	key_peg_full_radius = key_peg_radius + key_peg_border_width;
	key_peg_w = key_peg_full_radius * 2 + 1;
	key_peg_mutual_dist = 30 * SCALE;
	key_peg_offset_x = code_peg_offset_x + code_peg_mutual_dist * 4.5;
	key_peg_offset_y = row_offset_y - key_peg_mutual_dist / 2;

	row_peg_radius = key_peg_radius;
	row_peg_border_width = 2 * SCALE;
	row_peg_offset_x = row_offset_x;
	row_peg_offset_y = row_offset_y;

	correct_peg_offset_y = row_offset_y + 10.5 * row_height;
	correct_peg_offset_y += code_peg_radius + code_peg_border_width;

	button_width = 95 * SCALE;
	button_height = 95 * SCALE;
	button_border_width = 5 * SCALE;
	float button_mutual_distance = 115 * SCALE;
	float button_offset_y = selection_box_y + selection_box_height + 20 * SCALE;

	check_button.rect = (SDL_FRect) {
		selection_box_x,
		selection_box_y + selection_box_height + 20 * SCALE,
		button_width, button_height };
	check_button.border_width = button_border_width;

	resign_button.rect = (SDL_FRect) {
		selection_box_x + button_mutual_distance,
		button_offset_y,
		button_width, button_height };
	resign_button.border_width = button_border_width;

	random_button.rect = (SDL_FRect) {
		selection_box_x,
		button_offset_y + button_mutual_distance,
		button_width, button_height };
	random_button.border_width = button_border_width;

	smart_button.rect = (SDL_FRect) {
		selection_box_x + button_mutual_distance,
		button_offset_y + button_mutual_distance,
		button_width, button_height };
	smart_button.border_width = button_border_width;

	reset_button.rect = (SDL_FRect) {
		selection_box_x,
		button_offset_y + button_mutual_distance * 2,
		button_width, button_height };
	reset_button.border_width = button_border_width;

	quit_button.rect = (SDL_FRect) {
		selection_box_x + button_mutual_distance,
		button_offset_y + button_mutual_distance * 2,
		button_width, button_height };
	quit_button.border_width = button_border_width;
	float x, y;

	for (int row = 0; row < NUM_GUESSES; row++) {
		float row_y = row * row_height;

		for (int i = 0; i < CODE_LENGTH; i++) {
			float code_peg_x = code_peg_offset_x + code_peg_mutual_dist * i;
			float code_peg_y = code_peg_offset_y + row_y;

			code_pegs_rect[row][i] = (SDL_FRect) {
				code_peg_x - code_peg_full_radius, code_peg_y - code_peg_full_radius,
				code_peg_w, code_peg_w
			};

			clickablePegs[row * CODE_LENGTH + i].x = code_peg_x;
			clickablePegs[row * CODE_LENGTH + i].y = code_peg_y;
			clickablePegs[row * CODE_LENGTH + i].xOrig = code_peg_x;
			clickablePegs[row * CODE_LENGTH + i].yOrig = code_peg_y;

			x = key_peg_offset_x + key_peg_mutual_dist * (i % 2);
			y = key_peg_offset_y + row_y + key_peg_mutual_dist * (i / 2);
			key_pegs_rect[row][i] = (SDL_FRect) {
				x - key_peg_full_radius, y - key_peg_full_radius,
				key_peg_w, key_peg_w
			};
		}
		x = row_peg_offset_x;
		y = row_peg_offset_y + row_y;
		row_pegs_rect[row] = (SDL_FRect) {
			x - key_peg_full_radius, y - key_peg_full_radius,
			key_peg_w, key_peg_w
		};
	}

	for (int i = 0; i < NUM_COLORS; i++) {
		x = selection_peg_offset_x + code_peg_mutual_dist * (i%2);
		y = selection_peg_offset_y + code_peg_mutual_dist * (i/2);

		selection_pegs_rect[i] = (SDL_FRect) {
			x - code_peg_full_radius, y - code_peg_full_radius,
			code_peg_w, code_peg_w
		};

		clickablePegs[NUM_HOLES + i].x = x;
		clickablePegs[NUM_HOLES + i].y = y;
		clickablePegs[NUM_HOLES + i].xOrig = x;
		clickablePegs[NUM_HOLES + i].yOrig = y;
	}
	selected_peg_rect.w = code_peg_w;
	selected_peg_rect.h = code_peg_w;
}

void render_selection(SDL_Renderer* renderer, Peg* selectedPeg) {
	SDL_RenderTexture(renderer, selection_box_texture,
		NULL, &selection_box_rect);
	for (int i = 0; i < 6; i++) {
		if (selectedPeg == NULL ||
			selectedPeg->ptr != &selection[i])
		{
			SDL_RenderTexture(renderer, code_peg_textures[selection[i]],
				NULL, &selection_pegs_rect[i]);
		}
	}
}

void render_selected_peg(SDL_Renderer* renderer, Peg* peg) {
	if (peg != NULL) {
		selected_peg_rect.x = peg->x - code_peg_full_radius;
		selected_peg_rect.y = peg->y - code_peg_full_radius;

		SDL_RenderTexture(renderer, code_peg_textures[*peg->ptr],
			NULL, &selected_peg_rect);
	}
}

void render_board(SDL_Renderer* renderer) {
	SDL_RenderTexture(renderer, board_texture, NULL, &board_rect);
}

void render_row(SDL_Renderer* renderer, int row, int curGuess,
		char guess[CODE_LENGTH], char key[CODE_LENGTH], Peg* selectedPeg)
{
	if (row == curGuess)
		SDL_RenderTexture(renderer, key_peg_textures[KEY_WHITE],
			NULL, &row_pegs_rect[row]);
	else
		SDL_RenderTexture(renderer, key_peg_textures[KEY_BLANK],
			NULL, &row_pegs_rect[row]);

	for (int i = 0; i < CODE_LENGTH; i++) {
		if (selectedPeg != NULL && selectedPeg->ptr == &guess[i])
			SDL_RenderTexture(renderer, code_peg_textures[CODE_BLANK],
				NULL, &code_pegs_rect[row][i]);
		else
			SDL_RenderTexture(renderer, code_peg_textures[guess[i]],
				NULL, &code_pegs_rect[row][i]);
	}

	for (int i = 0; i < CODE_LENGTH; i++) {
		SDL_RenderTexture(renderer, key_peg_textures[key[i]],
			NULL, &key_pegs_rect[row][i]);
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
		SDL_RenderTexture(vars->renderer, button_textures[i], NULL, &buttons[i]->rect);
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

