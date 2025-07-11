#include "mastermind.h"
#include "definitions.h"
#include <stdio.h>

void check_guess(int* curGuess,
		char guess[CODE_LENGTH],
		char code[CODE_LENGTH],
		char key[CODE_LENGTH],
		GameState* gameState)
{
	if (*gameState != GAME_ONGOING) return;
	if (*curGuess >= NUM_GUESSES) {
		*gameState = GAME_LOST;
		printf("YOU LOST!\n");
		return;
	}
	// number of correctly guessed positions
	unsigned char correctPos = 0;
	// number of correctly guessed colors that are present
	// but potentially in wrong positions
	unsigned char correctColors = 0;

	// how many of each color in the guess and the code
	unsigned char guessColorCnt[NUM_WITH_BLANK] = {0};
	unsigned char codeColorCnt[NUM_WITH_BLANK] = {0};

	for(int i = 0; i < CODE_LENGTH; i++) {
		guessColorCnt[guess[i]]++;
		codeColorCnt[code[i]]++;
		if (guess[i] == code[i]) {
			correctPos++;
		}
	}

	for (int i = 0; i < NUM_WITH_BLANK; i++) {
		if (guessColorCnt[i] <= codeColorCnt[i]) {
			correctColors += guessColorCnt[i];
		} else {
			correctColors += codeColorCnt[i];
		}
	}

	for (int i = 0; i < correctPos; i++) {
		key[i] = KEY_RED;
	}
	for (int i = correctPos; i < correctColors; i++) {
		key[i] = KEY_WHITE;
	}
	for (int i = correctColors; i < CODE_LENGTH; i++) {
		key[i] = KEY_BLANK;
	}

	(*curGuess)++;

	if (correctPos == CODE_LENGTH) {
		*gameState = GAME_WON;
		printf("YOU WON!\n");
		return;
	}
	else if (*curGuess == NUM_GUESSES) {
		*gameState = GAME_LOST;
		printf("YOU LOST!\n");
		return;
	}
}

void reset_game(GameState* state, int* curGuess,
			char guesses[NUM_GUESSES][CODE_LENGTH],
			char keys[NUM_GUESSES][CODE_LENGTH])
{
	*state = GAME_ONGOING;
	*curGuess = 0;
	for (int i = 0; i < NUM_GUESSES; i++) {
		for (int j = 0; j < CODE_LENGTH; j++) {
			guesses[i][j] = CODE_BLANK;
			keys[i][j] = CODE_BLANK;
		}
	}
}
