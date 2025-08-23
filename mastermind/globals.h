#pragma once
#include <SDL3/SDL.h>
#include "../general/button.h"
#include "definitions.h"
#include "peg.h"

#define NUM_HOLES (NUM_GUESSES * CODE_LENGTH)
#define NUM_CLICKABLE_PEGS (NUM_HOLES + NUM_COLORS)

extern Peg clickablePegs[NUM_CLICKABLE_PEGS];

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float SCALE;

extern float code_peg_radius;
extern float code_peg_border_width;

#define NUM_BUTTONS 6
extern Button check_button, resign_button, random_button, smart_button, reset_button, quit_button;
extern Button* buttons[NUM_BUTTONS];
