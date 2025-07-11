#include "codemaker.h"
#include <stdlib.h>

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

void generate_random_code(char code[4]) {
	unsigned short numcode = rand();
	generate_code_bd(numcode, code);
}

