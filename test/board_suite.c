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
	Board *emptyBoard = initBoard(EMPTYSTR);
	CU_ASSERT_NOT_EQUAL(emptyBoard, NULL);
	CU_ASSERT_TRUE(emptyBoard->isValid);
	CU_ASSERT_TRUE(checkValidBoard(emptyBoard));
	deleteBoard(emptyBoard);

	Board *valid1 = initBoard(VALID1STR);
	CU_ASSERT_NOT_EQUAL(valid1, NULL);
	CU_ASSERT_TRUE(valid1->isValid);
	CU_ASSERT_TRUE(checkValidBoard(valid1));
	deleteBoard(valid1);

	Board *invalid1 = initBoard(INVALID1STR);
	CU_ASSERT_EQUAL(invalid1, NULL);
	deleteBoard(invalid1);
}

void test_get(void)
{
	Board *valid1 = initBoard(VALID1STR);
	CU_ASSERT_EQUAL(get(valid1, 3, 0), PIECE_1);
	CU_ASSERT_EQUAL(get(valid1, 3, 1), PIECE_2);
	CU_ASSERT_EQUAL(get(valid1, 3, 2), PIECE_2);
	CU_ASSERT_EQUAL(get(valid1, 3, 3), EMPTY);
	deleteBoard(valid1);
}

void test_add(void)
{
	Board *valid1 = initBoard(VALID1STR);
	CU_ASSERT_NOT_EQUAL(valid1, NULL);
	CU_ASSERT_EQUAL(valid1->turn, -1);

	CU_ASSERT_EQUAL(add(valid1, PIECE_2, 4), OK);
	CU_ASSERT_EQUAL(strlen(valid1->board), strlen(VALID2STR));
	CU_ASSERT_NSTRING_EQUAL(valid1->board, VALID2STR, sizeof(valid1->board));
	CU_ASSERT_EQUAL(valid1->turn, 0);
	CU_ASSERT_EQUAL(valid1->history[valid1->turn], 4);

	deleteBoard(valid1);

	Board *valid2 = initBoard(VALID1STR);
	CU_ASSERT_NOT_EQUAL(valid2, NULL);

	// VALID1STR -> VALID2STR
	CU_ASSERT_EQUAL(add(valid2, PIECE_2, 4), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID2STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, VALID2STR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 0);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 4);

	// VALID2STR -> VALID3STR
	CU_ASSERT_EQUAL(add(valid2, PIECE_1, 3), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID3STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, VALID3STR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 1);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 3);

	// VALID3STR -> VALID4STR
	CU_ASSERT_EQUAL(add(valid2, PIECE_1, 3), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID4STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, VALID4STR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 2);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 3);

	// failing adds
	CU_ASSERT_EQUAL(add(valid2, PIECE_2, 6), COLUMN_FULL);
	CU_ASSERT_EQUAL(valid2->turn, 2);
	CU_ASSERT_EQUAL(add(valid2, PIECE_2, -1), INVALID_INDEX);
	CU_ASSERT_EQUAL(valid2->turn, 2);
	CU_ASSERT_EQUAL(add(valid2, PIECE_2, 7), INVALID_INDEX);
	CU_ASSERT_EQUAL(valid2->turn, 2);
	CU_ASSERT_EQUAL(add(valid2, EMPTY, 2), INVALID_PIECE);
	CU_ASSERT_EQUAL(valid2->turn, 2);

	deleteBoard(valid2);
}

void test_revert(void)
{
	Board *empty = initBoard(EMPTYSTR);

	CU_ASSERT_NOT_EQUAL(empty, NULL);
	CU_ASSERT_EQUAL(revert(empty), INVALID_INDEX);

	CU_ASSERT_EQUAL(add(empty, PIECE_1, 3), OK);
	CU_ASSERT_EQUAL(empty->turn, 0);
	CU_ASSERT_EQUAL(empty->history[empty->turn], 3);

	CU_ASSERT_EQUAL(revert(empty), OK);
	CU_ASSERT_NSTRING_EQUAL(empty->board, EMPTYSTR, strlen(EMPTYSTR));
	CU_ASSERT_EQUAL(empty->turn, -1);

	add(empty, PIECE_1, 3); // turn 0
	char pos0[BOARD_STRING_SIZE];
	strcpy(pos0, empty->board);

	add(empty, PIECE_2, 2); // turn 1
	char pos1[BOARD_STRING_SIZE];
	strcpy(pos1, empty->board);

	add(empty, PIECE_1, 2); // turn 2

	revert(empty);
	CU_ASSERT_EQUAL(empty->turn, 1);
	CU_ASSERT_NSTRING_EQUAL(pos1, empty->board, strlen(pos1));

	revert(empty);
	CU_ASSERT_EQUAL(empty->turn, 0);
	CU_ASSERT_NSTRING_EQUAL(pos0, empty->board, strlen(pos0));

	revert(empty);
	CU_ASSERT_NSTRING_EQUAL(EMPTYSTR, empty->board, strlen(EMPTYSTR));

	deleteBoard(empty);
}

void test_stackHeight(void)
{
	Board *empty = initBoard(EMPTYSTR);
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		CU_ASSERT_EQUAL(empty->stackheight[i], 0);
	}
	deleteBoard(empty);

	Board *valid1 = initBoard(VALID1STR);
	CU_ASSERT_EQUAL(valid1->stackheight[0], 3);
	CU_ASSERT_EQUAL(valid1->stackheight[1], 4);
	CU_ASSERT_EQUAL(valid1->stackheight[2], 4);
	CU_ASSERT_EQUAL(valid1->stackheight[3], 3);
	CU_ASSERT_EQUAL(valid1->stackheight[4], 4);
	CU_ASSERT_EQUAL(valid1->stackheight[5], 4);
	CU_ASSERT_EQUAL(valid1->stackheight[6], 6);
	deleteBoard(valid1);
}
