#include "globals.h"

Peg clickablePegs[NUM_CLICKABLE_PEGS];

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 1200;
float SCALE = 1.0;

Button* buttons[NUM_BUTTONS] = {
		&check_button, &resign_button,
		&random_button, &smart_button,
		&reset_button, &quit_button };
