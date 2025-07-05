#pragma once
#include <stdio.h>
#include <time.h>

/*
Implementation of the Mastermind game. Refer to:
https://en.wikipedia.org/wiki/Mastermind_(board_game)

*/

#define CODE_LENGTH 4

#define CODE_RED 0
#define CODE_GREEN 1
#define CODE_BLUE 2
#define CODE_YELLOW 3
#define CODE_WHITE 4
#define CODE_BLACK 5
#define CODE_BLANK 6

#define NUM_COLORS 6
#define NUM_WITH_BLANK 7

#define KEY_RED 0
#define KEY_WHITE 4
#define KEY_BLANK 6

#define NUM_GUESSES 10

/*
	Following functions don't really generate a code from scratch,
	but instead convert a numerical code into a string code
	where each element corresponds to a color in the game.
	So you have to generate a numerical code first, probably using rand.
*/


// generates a code where blanks and duplicates are allowed
void generate_code_bd(unsigned short numcode, char code[CODE_LENGTH]) {
	// the number of choices, in this case 7 (number of colors + blank)
	int choices = NUM_WITH_BLANK;
	for (int i = 0; i < CODE_LENGTH; i++) {
	/* remainder will always be a value from 0 to 6 which
	   correspond to our colors plus the blank */
		code[i] = numcode % choices;
		numcode /= choices;
	}
}


// generates a code that allows duplicates but NOT blanks
void generate_code_xd(unsigned short numcode, char code[CODE_LENGTH]) {
	// same as previous function but number of choices excludes blank
	int choices = NUM_COLORS;
	for (int i = 0; i < CODE_LENGTH; i++) {
		code[i] = numcode % choices;
		numcode /= choices;
	}
}


// generates code with NO blanks and NO duplicates
void generate_code_xx(unsigned short numcode, char code[CODE_LENGTH]) {
// maps colors to a bool value that indicates whether it was used yet
	bool used[NUM_COLORS] = {false};
	int choices;

	for (int i = 0; i < CODE_LENGTH; i++) {
 /* in order to have no duplicates, we must decrease the number of
    available choices after choosing a color every time */
 		choices = NUM_COLORS - i;

		code[i] = numcode % choices;
		numcode /= choices;

// think of the selected number as an index to an array of yet unselected colors
// to have such an array we would need to remove selected colors from a full color array
// but instead of actually removing them, we can just skip through colors that were selected
		int skipped = 0;
		for (int j = 0; j <= code[i] + skipped; j++) {
			if(used[j]) skipped++;
		}
		code[i] += skipped;
		used[code[i]] = true;
	}
}


// generates code with no duplicates and up to a single blank
// you can think of this as the xx function but with blank being a seventh color
void generate_code_sbx(unsigned short numcode, char code[CODE_LENGTH]) {
	bool used[NUM_WITH_BLANK] = {false};
	int choices;

	for (int i = 0; i < CODE_LENGTH; i++) {
		choices = NUM_WITH_BLANK - i;
		code[i] = numcode % choices;
		numcode /= choices;

		int skipped = 0;
		for (int j = 0; j <= code[i] + skipped; j++) {
			if(used[j]) skipped++;
		}
		code[i] += skipped;
		used[code[i]] = true;
	}
}


// generates code with (possibly multiple) blanks but NO duplicates
// like the xx function but with blank being a special duplicable seventh color
void generate_code_mbx(unsigned short numcode, char code[CODE_LENGTH]) {
	bool used[NUM_COLORS] = {false};
	int choices;
	// choices decrease by this value instead of i
	int usedNonBlanks = 0;

	for (int i = 0; i < CODE_LENGTH; i++) {
		choices = NUM_WITH_BLANK - usedNonBlanks;
		code[i] = numcode % choices;
		numcode /= choices;

		if (code[i] != CODE_BLANK) {
			int skipped = 0;
			for (int j = 0; j <= code[i] + skipped; j++) {
				if(used[j]) skipped++;
			}
			code[i] += skipped;
			if (code[i] != CODE_BLANK) {
				used[code[i]] = true;
				usedNonBlanks++;
			}
		}
	}

}


void code_to_letters(char code[CODE_LENGTH], char letters[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) letters[i] = code[i] + 'A';
}

void letters_to_code(char letters[CODE_LENGTH], char code[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) code[i] = letters[i] - 'A';
}


void generate_random_code(char code[4]) {
	unsigned short numcode = rand();
	generate_code_bd(numcode, code);
}

typedef enum {
	GAME_ONGOING,
	GAME_WON,
	GAME_LOST,
	GAME_QUIT
} GameState;

void check_guess(int* curGuess,
		char guess[CODE_LENGTH],
		char code[CODE_LENGTH],
		char key[CODE_LENGTH],
		GameState* gameState)
{
	if (*gameState != GAME_ONGOING) return;
	if (*curGuess >= NUM_GUESSES) {
		*gameState = GAME_LOST;
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
		return;
	}
	else if (*curGuess == NUM_GUESSES) {
		*gameState = GAME_LOST;
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
