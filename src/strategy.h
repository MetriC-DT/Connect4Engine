#include "board.h"

// returns the available moves.
// first member of the returned int array is the number of legal moves.
// every number after that is the available move.
int *getAvailableMoves(Board *b);

// random move picker strategy.
int strategyRandom(Board *b);
