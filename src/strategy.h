#include "board.h"

// copies the available moves to *moves.
// ensure that moves can fit at most BOARD_WIDTH + 1 ints.
// (aka have moves initialized to moves[BOARD_WIDTH+1])
// first member of the moves array is the number of legal moves.
// every number after that is the available move.
void getAvailableMoves(Board *b, int *moves);

// random move picker strategy.
int strategyRandom(Board *b);
