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
	int *availableMoves = getAvailableMoves(b);
	CU_ASSERT_EQUAL(availableMoves[0], 7);

	free(availableMoves);
	free(b);

	b = initBoard(VALID1STR);
	availableMoves = getAvailableMoves(b);
	CU_ASSERT_EQUAL(availableMoves[0], 6);

	for (int i = 1; i <= availableMoves[0]; ++i) {
		CU_ASSERT_NOT_EQUAL(availableMoves[i], 6);
	}

	free(b);
	free(availableMoves);
}
