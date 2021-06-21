#ifndef STRATEGY_H
#define STRATEGY_H

#include "board.h"

typedef struct Pair {
	int value;
	int move;
} Pair;

// copies the available moves to *moves.
// ensure that moves can fit at most BOARD_WIDTH + 1 ints.
// (aka have moves initialized to moves[BOARD_WIDTH+1])
// first member of the moves array is the number of legal moves.
// every number after that is the available move.
void getAvailableMoves(Board *b, int *moves);

// random move picker strategy.
int strategyRandom(Board *b);

// alpha beta pruning. Returns the evaluation of the current position.
Pair strategyAlphaBeta(Board *b);

// static eval of board.
int eval(Board *b, int depth);

Pair negamax(Board *b, char currentPlayer, int depth, int alpha, int beta, int color);

extern const int EVALTABLE[BOARD_SIZE];

#define MAX_SCORE 10000

#define DEPTH 13

#endif
