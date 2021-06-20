#include <stdio.h>
#include <stdlib.h>

#include "strategy.h"

void getAvailableMoves(Board *b, int *moves)
{
	// moves available only when game has not been won.
	if (getWinner(b) != INCOMPLETE) {
		moves[0] = 0;
		return;
	}

	int validmoves = 0;
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		if (b->stackheight[i] < BOARD_HEIGHT) {
			moves[++validmoves] = i;
		}
	}

	// number of valid moves is the first element of array.
	moves[0] = validmoves;
}


// returns a random valid move.
// if no moves are available, returns -1.
int strategyRandom(Board *b)
{
	int moves[BOARD_WIDTH + 1];
	getAvailableMoves(b, moves);

	int movecount = moves[0];
	if (movecount <= 0)
		return -1;

	int index = rand() % movecount + 1;
	int selection = moves[index];
	return selection;
}
