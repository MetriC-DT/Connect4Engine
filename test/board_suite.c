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

void test_initboard(void)
{
	Board *emptyBoard = initBoard(EMPTYSTR);
	CU_ASSERT_NOT_EQUAL(emptyBoard, NULL);
	CU_ASSERT_TRUE(emptyBoard->isValid);
	CU_ASSERT_EQUAL(emptyBoard->emptycount, 42);
	CU_ASSERT_EQUAL(emptyBoard->winner, INCOMPLETE);
	deleteBoard(emptyBoard);

	Board *b1 = initBoard(VALID1STR);
	CU_ASSERT_NOT_EQUAL(b1, NULL);
	CU_ASSERT_TRUE(b1->isValid);
	CU_ASSERT_EQUAL(b1->emptycount, 21);
	CU_ASSERT_EQUAL(b1->winner, INCOMPLETE);
	deleteBoard(b1);

	b1 = initBoard(XWINSTR);
	CU_ASSERT_NOT_EQUAL(b1, NULL);
	CU_ASSERT_TRUE(b1->isValid);
	CU_ASSERT_EQUAL(b1->emptycount, 16);
	CU_ASSERT_EQUAL(b1->winner, PIECE_2);
	deleteBoard(b1);
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
	CU_ASSERT_EQUAL(get(valid1, 3, 1), PIECE_1);
	CU_ASSERT_EQUAL(get(valid1, 3, 2), PIECE_2);
	CU_ASSERT_EQUAL(get(valid1, 3, 3), EMPTY);
	CU_ASSERT_EQUAL(get(valid1, 6, 3), PIECE_2);
	CU_ASSERT_EQUAL(get(valid1, 7, 3), INVALID_CHAR);
	CU_ASSERT_EQUAL(get(valid1, -1, 3), INVALID_CHAR);
	deleteBoard(valid1);
}

void test_add(void)
{
	Board *valid1 = initBoard(VALID1STR);
	CU_ASSERT_NOT_EQUAL(valid1, NULL);
	CU_ASSERT_EQUAL(valid1->turn, -1);

	CU_ASSERT_EQUAL(add(valid1, 0), OK);
	CU_ASSERT_EQUAL(strlen(valid1->board), strlen(VALID2STR));
	CU_ASSERT_NSTRING_EQUAL(valid1->board, VALID2STR, sizeof(valid1->board));
	CU_ASSERT_EQUAL(valid1->turn, 0);
	CU_ASSERT_EQUAL(valid1->history[valid1->turn], 0);

	deleteBoard(valid1);

	Board *valid2 = initBoard(VALID1STR);
	CU_ASSERT_NOT_EQUAL(valid2, NULL);
	CU_ASSERT_EQUAL(valid2->winner, INCOMPLETE);

	// VALID1STR -> VALID2STR
	CU_ASSERT_EQUAL(add(valid2, 0), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID2STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, VALID2STR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 0);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 0);
	CU_ASSERT_EQUAL(valid2->winner, INCOMPLETE);

	// VALID2STR -> VALID3STR
	CU_ASSERT_EQUAL(add(valid2, 0), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID3STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, VALID3STR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 1);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 0);
	CU_ASSERT_EQUAL(valid2->winner, INCOMPLETE);

	// VALID3STR -> VALID4STR
	CU_ASSERT_EQUAL(add(valid2, 0), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID4STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, VALID4STR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 2);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 0);
	CU_ASSERT_EQUAL(valid2->winner, INCOMPLETE);

	// VALID4STR -> VALID5STR
	CU_ASSERT_EQUAL(add(valid2, 5), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID5STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, VALID5STR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 3);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 5);
	CU_ASSERT_EQUAL(valid2->winner, INCOMPLETE);

	// VALID5STR -> XWINSTR
	CU_ASSERT_EQUAL(add(valid2, 5), OK);
	CU_ASSERT_EQUAL(strlen(valid2->board), strlen(VALID5STR));
	CU_ASSERT_NSTRING_EQUAL(valid2->board, XWINSTR, sizeof(valid2->board));
	CU_ASSERT_EQUAL(valid2->turn, 4);
	CU_ASSERT_EQUAL(valid2->history[valid2->turn], 5);
	CU_ASSERT_EQUAL(valid2->winner, PIECE_2);

	deleteBoard(valid2);
}

void test_add_fail(void)
{
	// failing adds
	Board *b1 = initBoard(VALID1STR);
	CU_ASSERT_EQUAL(add(b1, 6), COLUMN_FULL);
	CU_ASSERT_EQUAL(b1->turn, -1);
	CU_ASSERT_EQUAL(add(b1, -1), INVALID_INDEX);
	CU_ASSERT_EQUAL(b1->turn, -1);
	CU_ASSERT_EQUAL(add(b1, 7), INVALID_INDEX);
	CU_ASSERT_EQUAL(b1->turn, -1);

	deleteBoard(b1);

	b1 = initBoard(XWINSTR);
	CU_ASSERT_EQUAL(add(b1, 3), GAME_OVER);
	deleteBoard(b1);
}

void test_revert(void)
{
	Board *empty = initBoard(EMPTYSTR);

	CU_ASSERT_NOT_EQUAL(empty, NULL);
	CU_ASSERT_EQUAL(revert(empty), INVALID_INDEX);

	CU_ASSERT_EQUAL(add(empty, 3), OK);
	CU_ASSERT_EQUAL(empty->turn, 0);
	CU_ASSERT_EQUAL(empty->history[empty->turn], 3);

	CU_ASSERT_EQUAL(revert(empty), OK);
	CU_ASSERT_NSTRING_EQUAL(empty->board, EMPTYSTR, strlen(EMPTYSTR));
	CU_ASSERT_EQUAL(empty->turn, -1);

	add(empty, 3); // turn 0
	char pos0[BOARD_STRING_SIZE];
	strcpy(pos0, empty->board);

	add(empty, 2); // turn 1
	char pos1[BOARD_STRING_SIZE];
	strcpy(pos1, empty->board);

	add(empty, 2); // turn 2

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

void test_tie(void) {
	Board *b = initBoard(EMPTYSTR);
	CU_ASSERT_EQUAL(getWinner(b), INCOMPLETE);

	// Plays entire game till tied
	for (u_long i = 0; i < strlen(DRAW_LINE); ++i) {
		int move = DRAW_LINE[i] - '0';
		add(b, move);

		if (i == strlen(DRAW_LINE) - 1) {
			CU_ASSERT_EQUAL(getWinner(b), TIE);
		}
		else {
			CU_ASSERT_EQUAL(getWinner(b), INCOMPLETE);
		}
	}
	deleteBoard(b);
}

void test_checkwin(void) {
	Board *b = initBoard(WINDIAG1);
	CU_ASSERT_EQUAL(b->winner, PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 0, 0), PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 1, 1), PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 2, 2), PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 3, 3), PIECE_2);
	deleteBoard(b);

	b = initBoard(XWINSTR);
	CU_ASSERT_EQUAL(b->winner, PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 2, 2), PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 3, 2), PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 4, 2), PIECE_2);
	CU_ASSERT_EQUAL(checkwin(b, 5, 2), PIECE_2);
	deleteBoard(b);

	b = initBoard(WINDIAG2);
	CU_ASSERT_EQUAL(b->winner, PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 1, 4), PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 2, 3), PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 3, 2), PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 4, 1), PIECE_1);
	deleteBoard(b);

	b = initBoard(WINVERT);
	CU_ASSERT_EQUAL(b->winner, PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 1, 0), PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 1, 1), PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 1, 2), PIECE_1);
	CU_ASSERT_EQUAL(checkwin(b, 1, 3), PIECE_1);
	deleteBoard(b);

	b = initBoard(EMPTY1STR);
	CU_ASSERT_EQUAL(b->winner, INCOMPLETE);
	if (get(b, 5, 0) != EMPTY)
		CU_ASSERT_EQUAL(checkwin(b, 5, 0), INCOMPLETE);
	deleteBoard(b);
}

void test_stackHeight(void)
{
	Board *empty = initBoard(EMPTYSTR);
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		CU_ASSERT_EQUAL(empty->stackheight[i], 0);
	}
	deleteBoard(empty);

	Board *valid1 = initBoard(VALID1STR);
	CU_ASSERT_EQUAL(valid1->stackheight[0], 1);
	CU_ASSERT_EQUAL(valid1->stackheight[1], 3);
	CU_ASSERT_EQUAL(valid1->stackheight[2], 3);
	CU_ASSERT_EQUAL(valid1->stackheight[3], 3);
	CU_ASSERT_EQUAL(valid1->stackheight[4], 4);
	CU_ASSERT_EQUAL(valid1->stackheight[5], 1);
	CU_ASSERT_EQUAL(valid1->stackheight[6], 6);
	deleteBoard(valid1);
}
