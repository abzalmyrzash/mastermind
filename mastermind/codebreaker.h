#pragma once
#include "definitions.h"
#include <stdbool.h>

void make_random_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH]);

// converts a code to an index in the space of possible codes
int code_to_index(char code[CODE_LENGTH]);

// reverse
void index_to_code(int index, char code[CODE_LENGTH]);

#define IMPOSSIBLE -1
#define POSSIBLE 0
#define DEFINITE 1
#define INDEFINITE -1

static bool codePossibility[CODE_SPACE];
static int numPossibleCodes = 0;

// used for continuing analysis where it last left off
static int prevGuessI;

void reset_code_breaker();

void analyze_prev_guesses(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH]);

void make_smart_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH]);
