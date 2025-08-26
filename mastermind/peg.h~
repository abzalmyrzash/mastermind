#pragma once

typedef enum {
	PEG_TYPE_SELECTION,
	PEG_TYPE_HOLE
} PegType;

typedef struct {
	float x, y;
	float xOrig, yOrig;
	PegType type;
	bool isClicked;
	char* ptr;
} Peg;

void swap_peg_values(Peg* a, Peg* b);
