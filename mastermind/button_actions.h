#pragma once
#include "../general/button.h"

int check_button_action (ButtonState* buttonState, void* data);

int reset_button_action (ButtonState* buttonState, void* data);

int resign_button_action (ButtonState* buttonState, void* data);

int quit_button_action (ButtonState* buttonState, void* data);

int random_button_action (ButtonState* buttonState, void* data);

int smart_button_action (ButtonState* buttonState, void* data);

void init_buttons();
