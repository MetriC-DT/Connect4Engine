#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <limits.h>
#include <immintrin.h>

#include "strategy.h"
#include "board.h"

// Evaluation table for number of possible 4-in-a-rows
const int EVALTABLE[BOARD_SIZE] = {
	3, 4, 5,  7,  5,  4, 3,
	4, 6, 8,  10, 8,  6, 4,
	5, 8, 11, 13, 11, 8, 5,
	5, 8, 11, 13, 11, 8, 5,
	4, 6, 8,  10, 8,  6, 4,
	3, 4, 5,  7,  5,  4, 3
};


void getAvailableMoves(Board *b, int *moves)
{
	// moves available only when game has not been won.
	if (getWinner(b) != INCOMPLETE) {
		moves[0] = 0;
		return;
	}

	// move ordering
	int validmoves = 0;
	int col = BOARD_WIDTH / 2;
	int off = 0;
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		off = (i % 2 == 0) ? i : -i;
		col = col + off;
		if (b->stackheight[col] < BOARD_HEIGHT) {
			moves[++validmoves] = col;
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


// uses alpha beta pruning to return the next valid move.
// if no moves are available, returns -1 as the Pair.move.
// Still returns evaluation as Pair.value.
Pair strategyAlphaBeta(Board *b)
{
	int color = (b->currentPlayer == PIECE_1) ? 1 : -1;
	int alpha = -MAX_SCORE;
	int beta = MAX_SCORE;

	Pair p;
	if (color == 1)
		p = negamax(b, b->currentPlayer, MIN_DEPTH, alpha, beta, color);
	else
		p = negamax(b, b->currentPlayer, MIN_DEPTH, -beta, -alpha, color);

	return p;
}

Pair negamax(Board *b, char currentPlayer, int depth, int alpha, int beta, int color)
{
	Pair p;
	p.move = -1;

	if (getWinner(b) != INCOMPLETE || depth == 0) {
		p.value = color * eval(b, depth);
		return p;
	}

	int moves[BOARD_WIDTH + 1];
	getAvailableMoves(b, moves);
	int movecount = moves[0];

	p.value = INT_MIN;
	for (int i = 1; i <= movecount; ++i) {
		add(b, moves[i]);

		int evalVal = -negamax(b, currentPlayer, depth - 1, -beta, -alpha, -color).value;

		revert(b);

		if (evalVal > p.value) {
			p.move = moves[i];
			p.value = evalVal;
		}

		alpha = MAX(alpha, p.value);
		if (alpha >= beta)
			break;
	}

	return p;
}


int eval(Board *b, int depth)
{
	if (getWinner(b) == PIECE_1) {
		return depth + MAX_SCORE;
	}
	else if (getWinner(b) == PIECE_2) {
		return -(depth + MAX_SCORE);
	}
	else if (getWinner(b) == TIE) {
		return 0;
	}

	int sum = 0;
	int row, col, piece;

	for (int n = 0; n < BOARD_SIZE; ++n) {
		row = n / BOARD_WIDTH;
		col = n % BOARD_WIDTH;
		piece = get(b, col, row);

		// we replace rowFromBottom with i because of board vert symmetry
		// int rowFromBottom = BOARD_HEIGHT - i - 1;
		if (piece == PIECE_1)
			sum += EVALTABLE[BOARD_WIDTH * row + col];
		else if (piece == PIECE_2)
			sum -= EVALTABLE[BOARD_WIDTH * row + col];
	}

	return sum;
}
