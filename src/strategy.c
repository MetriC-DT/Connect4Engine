#include <stdio.h>
#include <stdlib.h>

#include "strategy.h"

int *getAvailableMoves(Board *b)
{
	// moves available only when game has not been won.
	if (getWinner(b) != INCOMPLETE) {
		return NULL;
	}
	// adds one to include array size number at start.
	int arrsize = BOARD_WIDTH + 1;
	int *movelist = (int *) malloc(sizeof(int) * arrsize);
	if (movelist == NULL) {
		return NULL;
	}

	int validmoves = 0;
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		if (b->stackheight[i] < BOARD_HEIGHT) {
			movelist[++validmoves] = i;
		}
	}

	// number of valid moves is the first element of array.
	movelist[0] = validmoves;
	return movelist;
}


// returns a random valid move.
// if no moves are available, returns -1.
int strategyRandom(Board *b)
{
	int* moves = getAvailableMoves(b);
	if (moves == NULL)
		return -1;

	int movecount = moves[0];
	if (movecount <= 0)
		return -1;

	int index = rand() % movecount + 1;
	int selection = moves[index];
	free(moves);
	return selection;
}
