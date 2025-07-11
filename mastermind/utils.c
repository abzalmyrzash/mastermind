#include "utils.h"

void code_to_letters(char code[CODE_LENGTH], char letters[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) letters[i] = code[i] + 'A';
}

void letters_to_code(char letters[CODE_LENGTH], char code[CODE_LENGTH]) {
	for (int i = 0; i < CODE_LENGTH; i++) code[i] = letters[i] - 'A';
}
