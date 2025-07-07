#pragma once

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

// total number of possible codes (7^4)
#define CODE_SPACE 2401

void code_to_letters(char code[CODE_LENGTH], char letters[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) letters[i] = code[i] + 'A';
}

void letters_to_code(char letters[CODE_LENGTH], char code[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) code[i] = letters[i] - 'A';
}
