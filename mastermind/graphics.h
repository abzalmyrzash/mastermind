#include "definitions.h"
#pragma once
#include "variables.h"
#include "../general/button.h"

void init_graphics_variables(char guesses[NUM_GUESSES][CODE_LENGTH]);

void calculate_graphics_variables();

void create_textures(SDL_Renderer* renderer);

void destroy_textures();

void render_selection(SDL_Renderer* renderer, Peg* selectedPeg);

void render_selected_peg(SDL_Renderer* renderer, Peg* peg);

void render_board(SDL_Renderer* renderer);

void render_row(SDL_Renderer* renderer, int row, int curGuess,
		char guess[CODE_LENGTH], char key[CODE_LENGTH], Peg* selectedPeg);

void render_rows(SDL_Renderer* renderer, int curGuess,
		char guesses[NUM_GUESSES][CODE_LENGTH],
		char keys[NUM_GUESSES][CODE_LENGTH], Peg* selectedPeg);

void render_correct_code(SDL_Renderer* renderer, char code[CODE_LENGTH]);

void render_everything(GameVariables* vars);
