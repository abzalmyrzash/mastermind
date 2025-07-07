#pragma once
#include "mastermind_definitions.h"
#include <stdlib.h>
#include <stdbool.h>

void make_random_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH])
{
	unsigned short randomNumber = rand();
	int choices = NUM_WITH_BLANK;
	for (int i = 0; i < CODE_LENGTH; i++)
	{
		guesses[curGuessI][i] = randomNumber % choices;
		randomNumber /= choices;
	}
}

// converts a code to an index in the space of possible codes
int code_to_index(char code[CODE_LENGTH]) {
	int index = 0;
	int exponent = 1;
	for (int i = 0; i < CODE_LENGTH; i++) {
		index += code[i] * exponent;
		exponent *= NUM_WITH_BLANK;
	}
	return index;
}

// reverse
void index_to_code(int index, char code[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) {
		code[i] = index % NUM_WITH_BLANK;
		index /= NUM_WITH_BLANK;
	}
}

static int colorPossibility[NUM_WITH_BLANK];
// -1 - this color is definitely not present
// 0 - this color is possibly, but not definitely present
// 1 to 4 - how many times this color is definitely present

#define IMPOSSIBLE -1
#define POSSIBLE 0
#define DEFINITE 1
#define INDEFINITE -1

static int numPossibleColors;

static int definitePositions[CODE_LENGTH];
// -1 - this code position is unknown
// 0 to 6 - code position is definitely this color

static bool codePossibility[CODE_SPACE];

static int prevGuessI;
// used for continuing analysis where it last left off

static int numDefiniteColors;
static int numUniqDefiniteColors;

// what positions are possible/impossible/definite for a color
static int positionPossibility[NUM_WITH_BLANK][CODE_LENGTH];

// number of definite positions for color
static int numDefPosForColor[NUM_WITH_BLANK];

// number of possible positions for color
static int numPosPosForColor[NUM_WITH_BLANK];

void reset_code_breaker() {
	prevGuessI = 0;
	numPossibleColors = NUM_WITH_BLANK;
	numDefiniteColors = 0;
	numUniqDefiniteColors = 0;

	for (int i = 0; i < NUM_WITH_BLANK; i++) {
		colorPossibility[i] = POSSIBLE;
		numDefPosForColor[i] = 0;
		numPosPosForColor[i] = CODE_LENGTH;
		for (int j = 0; j < CODE_LENGTH; j++) {
			positionPossibility[i][j] = POSSIBLE;
		}
	}
	for (int i = 0; i < CODE_LENGTH; i++) {
		definitePositions[i] = INDEFINITE;
	}
	for (int i = 0; i < CODE_SPACE; i++) {
		codePossibility[i] = true;
	}
}

static bool isColorPossible(char color) {
	return colorPossibility[color] == POSSIBLE;
}

static bool isColorDefinite(char color) {
	return colorPossibility[color] >= DEFINITE;
}

static bool isColorImpossible(char color) {
	return colorPossibility[color] == IMPOSSIBLE;
}

void analyze_prev_guesses(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH])
{
	for (int i = prevGuessI; i < curGuessI; i++) {
		char* guess = guesses[i];
		int numCorrectColors = 0;
		int numCorrectPos = 0;
		int numWrongPos = 0;
		int cntColors[NUM_WITH_BLANK] = {0};
		int numUniqColors = 0;
		char uniqColors[CODE_LENGTH];
		int numDefiniteColorsHere = 0;
		int numUniqDefiniteColorsHere = 0;
	
		for (int j = 0; j < CODE_LENGTH; j++) {
			if (keys[i][j] == KEY_RED) {
				numCorrectPos++;
				numCorrectColors++;
			}
			else if (keys[i][j] == KEY_WHITE) {
				numCorrectColors++;
				numWrongPos++;
			}

			if (cntColors[guess[j]]++ == 0) {
				uniqColors[numUniqColors++] = guess[j];
			}
			
			if (colorPossibility[guess[j]] >= DEFINITE) {
				numDefiniteColorsHere++;
				if (cntColors[guess[j]] == 1) {
					numUniqDefiniteColorsHere++;
				}
			}
		}
		int numNewCorrectColors = numCorrectColors - numDefiniteColorsHere;
		int numNewUniqColors = numUniqColors - numUniqDefiniteColorsHere;
		printf("New correct colors: %d\n", numNewCorrectColors);
		
		if (numNewCorrectColors == 0) {
			for (int j = 0; j < numUniqColors; j++) {
				char color = uniqColors[j];
				if (isColorPossible(color)) {
					colorPossibility[color] = IMPOSSIBLE;
					numPossibleColors--;
					for (int k = 0; k < CODE_LENGTH; k++) {
						positionPossibility[color][k] = IMPOSSIBLE;
					}
				}
			}
			if (numWrongPos == 0) {
				for (int j = 0; j < CODE_LENGTH; j++) {
					if (isColorDefinite(guess[j])) {
						definitePositions[j] = guess[j];
						positionPossibility[guess[j]][j] = DEFINITE;
						numDefPosForColor[guess[j]]++;
						numPosPosForColor[guess[j]]--;
					}
				}
			} else if (numWrongPos == numDefiniteColorsHere) {
				for (int j = 0; j < CODE_LENGTH; j++) {
					if (isColorDefinite(guess[j])) {
						positionPossibility[guess[j]][j] = IMPOSSIBLE;
						numPosPosForColor[guess[j]]--;
					}
				}
			}
		}
		else if (numNewUniqColors == 1) {
			for (int j = 0; j < CODE_LENGTH; j++) {
				if (isColorPossible(guess[j])) {
					colorPossibility[guess[j]] = numNewCorrectColors;
					numDefiniteColors += numNewCorrectColors;
					numUniqDefiniteColors++;
					numPossibleColors--;
					break;
				}
			}
		}
		printf("Definite colors: %d; Unique: %d\n",
				numDefiniteColors, numUniqDefiniteColors);
		if (numDefiniteColors == CODE_LENGTH) {
			for (int j = 0; j < NUM_WITH_BLANK; j++) {
				if (colorPossibility[j] == POSSIBLE) {
					colorPossibility[j] = IMPOSSIBLE;
					numPossibleColors--;
				}
			}
		}
		else if (numPossibleColors == 1) {
			for (int j = 0; j < NUM_WITH_BLANK; j++) {
				if (colorPossibility[j] == POSSIBLE) {
					colorPossibility[j] = CODE_LENGTH - numDefiniteColors;
					numPossibleColors--;
				}
			}
		}
	}
	prevGuessI = curGuessI;
}

void make_smart_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH])
{
	analyze_prev_guesses(curGuessI, guesses, keys);

	char* curGuess = guesses[curGuessI];
	printf("Number of possible colors: %d\n", numPossibleColors);
	printf("Color possibility: ");
	for (int i = 0; i < NUM_WITH_BLANK; i++) {
		printf("%d ", colorPossibility[i]);
	}
	printf("\n");
	printf("Definite positions: ");
	for (int i = 0; i < CODE_LENGTH; i++) {
		printf("%d ", definitePositions[i]);
	}
	printf("\n");

	int definiteColorCnt = 0;
	bool posTaken[CODE_LENGTH] = {false};
	int numPosTaken = 0;

	for (int pos = 0; pos < CODE_LENGTH; pos++) {
		if (definitePositions[pos] != INDEFINITE) {
			posTaken[pos] = true;
			numPosTaken++;
			curGuess[pos] = definitePositions[pos];
		}
	}

	int randNum = rand();
	printf("%d\n", randNum);
	for (int i = 0; i < NUM_WITH_BLANK; i++) {
		int numPosToTake = colorPossibility[i] - numDefPosForColor[i];
		
		for (int j = 0; j < numPosToTake; j++) {
			int randomFactor = randNum % (numPosPosForColor[i] - numPosTaken);
			int pos = 0;
			for (; pos < CODE_LENGTH; pos++) {
				if (!posTaken[pos] && positionPossibility[i][pos] == POSSIBLE) {
					randomFactor--;
				}
				if (randomFactor < 0) break;
			}
			printf("%d ", pos);
			posTaken[pos] = true;
			numPosTaken++;
			curGuess[pos] = i;
		}
	}
	char letters[4];
	code_to_letters(curGuess, letters);
	printf("%4s\n", letters);

	if (numDefiniteColors == CODE_LENGTH) return;

	for (int i = 0; i < NUM_WITH_BLANK; i++) {
		if (colorPossibility[i] == 0) {
			for (int pos = 0; pos < CODE_LENGTH; pos++) {
				if(!posTaken[pos]) {
					posTaken[pos] = true;
					numPosTaken++;
					curGuess[pos] = i;
				}
			}
			return;
		}
	}
}
