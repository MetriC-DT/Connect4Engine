#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "board.h"

Board emptyBoard = {
	"_______"
	"_______"
	"_______"
	"_______"
	"_______"
	"_______",
	false
};

Board valid1 = {
	"______X"
	"______X"
	"_OX_OOX"
	"OXOXOOO"
	"OOOXXXX"
	"OOOOOOO",
	false
};

Board invalid1 = {
	"_______"
	"_______"
	"___O___"
	"_______"
	"_______"
	"_______",
	false
};

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
	CU_ASSERT_TRUE(checkValidBoard(&emptyBoard));
	CU_ASSERT_TRUE(emptyBoard.isValid);
	CU_ASSERT_TRUE(checkValidBoard(&valid1));
	CU_ASSERT_TRUE(valid1.isValid);
}

void test_get(void)
{
	CU_ASSERT_EQUAL(get(&invalid1, 2, 3), PIECE_1);
}
