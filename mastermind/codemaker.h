#pragma once
#include <stdbool.h>
#include "definitions.h"

/*
	Following functions don't really generate a code from scratch,
	but instead convert a numerical code into a string code
	where each element corresponds to a color in the game.
	So you have to generate a numerical code first, probably using rand.
*/


// generates a code where blanks and duplicates are allowed
void generate_code_bd(unsigned short numcode, char code[CODE_LENGTH]);

// generates a code that allows duplicates but NOT blanks
void generate_code_xd(unsigned short numcode, char code[CODE_LENGTH]);

// generates code with NO blanks and NO duplicates
void generate_code_xx(unsigned short numcode, char code[CODE_LENGTH]);

// generates code with no duplicates and up to a single blank
// you can think of this as the xx function but with blank being a seventh color
void generate_code_sbx(unsigned short numcode, char code[CODE_LENGTH]);

// generates code with (possibly multiple) blanks but NO duplicates
// like the xx function but with blank being a special duplicable seventh color
void generate_code_mbx(unsigned short numcode, char code[CODE_LENGTH]);

void generate_random_code(char code[4]);
