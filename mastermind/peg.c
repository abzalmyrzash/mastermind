#include "peg.h"

void swap_peg_values(Peg* a, Peg* b) {
	char tmp = *a->ptr;
	*a->ptr = *b->ptr;
	*b->ptr = tmp;
}
