a.out: main.c general/* mastermind/*
	gcc main.c general/*.c mastermind/*.c -lm -lSDL3
