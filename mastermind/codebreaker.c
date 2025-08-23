#include "codebreaker.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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

void reset_code_breaker() {
	prevGuessI = 0;
	numPossibleCodes = CODE_SPACE;
	possibleCodeI = 0;

	for (int i = 0; i < CODE_SPACE; i++) {
		codePossibility[i] = true;
		possibleCodes[i] = i;
	}
}

void analyze_prev_guesses(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH])
{
	int possibleCodeCnt = 0;
	for (int i = prevGuessI; i < curGuessI; i++) {
		char* guess = guesses[i];
		int correctColors = 0;
		int correctPos = 0;
	
		for (int j = 0; j < CODE_LENGTH; j++) {
			if (keys[i][j] == KEY_RED) {
				correctPos++;
				correctColors++;
			}
			else if (keys[i][j] == KEY_WHITE) {
				correctColors++;
			}
		}

		char code[4];
		unsigned char guessColorCnt[NUM_WITH_BLANK] = {0};
		for (int j = 0; j < CODE_LENGTH; j++) {
			guessColorCnt[guess[j]]++;
		}
		possibleCodeCnt = 0;
		for (int j = 0; j < numPossibleCodes; j++) {
			int c = possibleCodes[j];
			int matchingPos = 0;
			int matchingColors = 0;
			unsigned char codeColorCnt[NUM_WITH_BLANK] = {0};
			index_to_code(c, code);
			for (int j = 0; j < CODE_LENGTH; j++) {
				codeColorCnt[code[j]]++;
				if (guess[j] == code[j]) {
					matchingPos++;
				}
			}
			for (int j = 0; j < NUM_WITH_BLANK; j++) {
				if (guessColorCnt[j] <= codeColorCnt[j]) {
					matchingColors += guessColorCnt[j];
				} else {
					matchingColors += codeColorCnt[j];
				}
			}
			if (matchingColors != correctColors || matchingPos != correctPos) {
				codePossibility[c] = false;
			}
			else {
				possibleCodes[possibleCodeCnt++] = c;
			}
		}
		numPossibleCodes = possibleCodeCnt;
	}
	prevGuessI = curGuessI;
	printf("Number of possible codes: %d\n", numPossibleCodes);
}

void make_smart_guess(int curGuessI,
	char guesses[NUM_GUESSES][CODE_LENGTH],
	char keys[NUM_GUESSES][CODE_LENGTH])
{
	if (prevGuessI < curGuessI) {
		analyze_prev_guesses(curGuessI, guesses, keys);
		possibleCodeI = 0;
	}

	char* curGuess = guesses[curGuessI];
	int c = possibleCodes[possibleCodeI++];
	possibleCodeI %= numPossibleCodes;
	index_to_code(c, curGuess);
}
