#pragma once

typedef enum {
	PEG_TYPE_SELECTION,
	PEG_TYPE_HOLE
} PegType;

typedef struct {
	float x, y;
	PegType type;
	bool isClicked;
	char* ptr;
} Peg;

