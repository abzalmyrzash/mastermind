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

static int colorPossibility[NUM_WITH_BLANK];
// -1 - this color is definitely not present
// 0 - this color is possibly, but not definitely present
// 1 to 4 - how many times this color is definitely present
static int numPossibleColors;


static int definitePositions[CODE_LENGTH];
// -1 - this code position is unknown
// 0 to 6 - code position is definitely this color
static int numDefinitePositions;

static bool codePossibility[CODE_SPACE];

static int prevGuessI;
// used for continuing analysis where it last left off

static int numDefiniteColors;
static int numUniqDefiniteColors;

static int definiteColors[CODE_LENGTH];

// what positions are possible/impossible/definite for a color
static int positionPossibility[NUM_WITH_BLANK][CODE_LENGTH];

// number of definite positions for color
static int numDefPosForColor[NUM_WITH_BLANK];

// number of possible positions for color
static int numPosPosForColor[NUM_WITH_BLANK];

void reset_code_breaker();

static bool isColorPossible(char color);

static bool isColorDefinite(char color);

static bool isColorImpossible(char color);

void analyze_prev_guesses(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH]);

void make_smart_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH]);
