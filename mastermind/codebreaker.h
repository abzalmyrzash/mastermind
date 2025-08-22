#pragma once
#include "definitions.h"
#include <stdbool.h>

void make_random_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH]);

// converts a code to an index in the space of possible codes
int code_to_index(char code[CODE_LENGTH]);

// reverse
void index_to_code(int index, char code[CODE_LENGTH]);

static bool codePossibility[CODE_SPACE];
static int numPossibleCodes;
static int possibleCodes[CODE_SPACE];

// used for continuing analysis where it last left off
static int prevGuessI;

// used for cycling through possible codes
static int possibleCodeI;

void reset_code_breaker();

void analyze_prev_guesses(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH]);

void make_smart_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH]);
