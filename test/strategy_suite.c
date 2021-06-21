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

	free(b);

	b = initBoard(VALID1STR);
	getAvailableMoves(b, availableMoves);
	CU_ASSERT_EQUAL(availableMoves[0], 6);

	for (int i = 1; i <= availableMoves[0]; ++i) {
		CU_ASSERT_NOT_EQUAL(availableMoves[i], 6);
	}

	free(b);
}

void test_eval(void)
{
	Board *b = initBoard(EMPTYSTR);
	CU_ASSERT_EQUAL(eval(b, 0), 0);
	free(b);

	b = initBoard(VALID1STR);
	CU_ASSERT_EQUAL(eval(b, 0), 2);

	add(b, 0);
	CU_ASSERT_EQUAL(eval(b, 0), -2);
	free(b);
}
