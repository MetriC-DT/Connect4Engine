#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "strategy.h"
#include "strategy_suite.h"
#include "board.h"
#include "test_boards.h"

int init_suite_strategy(void)
{
	return 0;
}

int clean_suite_strategy(void)
{
	return 0;
}

void test_ValidMoves(void)
{
	Board *b = initBoard(EMPTYSTR);
	int availableMoves[BOARD_WIDTH + 1];
	getAvailableMoves(b, availableMoves);
	CU_ASSERT_EQUAL(availableMoves[0], 7);

	deleteBoard(b);

	b = initBoard(VALID1STR);
	getAvailableMoves(b, availableMoves);
	CU_ASSERT_EQUAL(availableMoves[0], 6);

	for (int i = 1; i <= availableMoves[0]; ++i) {
		CU_ASSERT_NOT_EQUAL(availableMoves[i], 6);
	}

	deleteBoard(b);
}

void test_eval(void)
{
	Board *b = initBoard(EMPTYSTR);
	CU_ASSERT_EQUAL(eval(b, 0), 0);
	deleteBoard(b);

	b = initBoard(VALID1STR);
	CU_ASSERT_EQUAL(eval(b, 0), 2);

	add(b, 0);
	CU_ASSERT_EQUAL(eval(b, 0), -2);
	deleteBoard(b);
}

void test_canWin(void)
{
	// piece 1 will win in this line.
	char *oWinString = "33333641111325545455152264404016060660202";

	Board *b = initBoard(EMPTYSTR);
	for (unsigned long i = 0; i < strlen(oWinString) - MIN_DEPTH; ++i) {
		Status status = add(b, oWinString[i] - '0');
		CU_ASSERT_EQUAL(status, OK);
	}

	int turncount = 0;
	while (getWinner(b) == INCOMPLETE) {
		int col = strategyAlphaBeta(b).move;
		Status status = add(b, col);
		CU_ASSERT_EQUAL(status, OK);
		++turncount;
	}

	CU_ASSERT_EQUAL(getWinner(b), PIECE_1);

	// must stay alive as long as possible.
	CU_ASSERT_EQUAL(turncount, MIN_DEPTH);

	deleteBoard(b);
}
