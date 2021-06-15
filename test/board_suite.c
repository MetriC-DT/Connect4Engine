#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "board.h"
#include "board_suite.h"
#include "test_boards.h"

int init_suite_board(void)
{
	return 0;
}

int clean_suite_board(void)
{
	return 0;
}

void test_checkValidBoard(void)
{
	CU_ASSERT_FALSE(emptyBoard.isValid);
	CU_ASSERT_TRUE(checkValidBoard(&emptyBoard));
	CU_ASSERT_TRUE(emptyBoard.isValid);

	CU_ASSERT_FALSE(valid1.isValid);
	CU_ASSERT_TRUE(checkValidBoard(&valid1));
	CU_ASSERT_TRUE(valid1.isValid);

	CU_ASSERT_FALSE(invalid1.isValid);
	CU_ASSERT_FALSE(checkValidBoard(&invalid1));
	CU_ASSERT_FALSE(invalid1.isValid);
}

void test_get(void)
{
	CU_ASSERT_EQUAL(get(&invalid1, 3, 3), PIECE_1);
}
