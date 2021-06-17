#include <sys/param.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"


// checks whether all the stacks are valid.
// Validity just checks the board for any
// floating pieces.
bool stackCheck(Board *board);

// checks whether a given board has a completed game.
// Should only be used on initialization.
char checkwinInit(Board *board);

// does same thing as get, but skips check.
char fastget(Board *board, int col, int row);

// checks for checkwin
char checkHorizontal(Board *board, int col, int row, char c);
char checkVertical(Board *board, int col, int row, char c);
char checkDiagonals(Board *board, int col, int row, char c);


/*****************************************************************/

Status add(Board *board, char piece, int column){
	if (board == NULL || !board->isValid || board->winner != INCOMPLETE) {
		return BOARD_INVALID;
	}
	else if (piece != PIECE_1 && piece != PIECE_2) {
		return INVALID_PIECE;
	}
	else if (column < 0 || column >= BOARD_WIDTH) {
		return INVALID_INDEX;
	}
	else if (board->stackheight[column] == BOARD_HEIGHT) {
		return COLUMN_FULL;
	}
	else {
		int rowFromTop = BOARD_HEIGHT - (++board->stackheight[column]);
		board->board[rowFromTop * BOARD_WIDTH + column] = piece;
		board->history[++board->turn] = column;
		--board->emptycount;
		board->winner = checkwin(board, column, board->stackheight[column] - 1);

		return OK;
	}
}


Status revert(Board *board) {
	if (board == NULL || !board->isValid) {
		return BOARD_INVALID;
	}
	else if (board->turn < 0) {
		return INVALID_INDEX;
	}
	else {
		int prevCol = board->history[board->turn--];
		int rowFromBottom = --board->stackheight[prevCol];
		int rowFromTop = BOARD_HEIGHT - rowFromBottom - 1;
		board->board[rowFromTop * BOARD_WIDTH + prevCol] = EMPTY;
		++board->emptycount;
		board->winner = INCOMPLETE;
		return OK;
	}
}


// does same thing as get, but skips check.
char fastget(Board *board, int col, int row) {
	int rowFromTop = BOARD_HEIGHT - row - 1;
	return board->board[rowFromTop * BOARD_WIDTH + col];
}


/*
 * Columns measured from the left 0 -> 6
 * Rows measured from the bottom 0 -> 5
 * Ex: The O is on column 3, row 0
 * _______
 * _______
 * _______
 * _______
 * _______
 * ___O___
 */
char get(Board *board, int col, int row) {
	if (board != NULL &&
			0 <= col && col < BOARD_WIDTH &&
			0 <= row && row < BOARD_HEIGHT)
	{
		return fastget(board, col, row);
	}
	return INVALID_CHAR;
}


/**
 * Used only for checkValidBoard(). Checks for floating pieces.
 * As well as determining the stack height.
 */
bool stackCheck(Board *board) {
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		bool reachedStackTop = false;
		for (int j = 0; j < BOARD_HEIGHT ; ++j) {
			if (get(board, i, j) == EMPTY && !reachedStackTop) {
				// case for hitting top of stack
				reachedStackTop = true;
				board->stackheight[i] = j;
			}
			else if (get(board, i, j) != EMPTY && reachedStackTop) {
				// case for floating block
				return false;
			}
			else if (j == BOARD_HEIGHT - 1 && !reachedStackTop) {
				// case for full stack
				board->stackheight[i] = BOARD_HEIGHT;
			}
		}
	}
	return true;
}


/**
 * Determines whether a board is valid.
 * Validity means there are no "floating" pieces.
 */
bool checkValidBoard(Board *board){
	if (board != NULL && board->isValid) {
		return true;
	}
	else if (board != NULL && stackCheck(board)) {
		board->isValid = true;
		return true;
	}
	else {
		board->isValid = false;
		return false;
	}
}

Board* initBoard(char *boardString) {
	if (boardString != NULL && checkString(boardString)) {
		Board *b = (Board *) malloc(sizeof(Board));
		if (b == NULL) {
			return NULL;
		}
		strcpy(b->board, boardString);
		b->isValid = false;
		b->winner = INCOMPLETE;

		// begins at -1 in order to have zero indexed when the first element is added to history.
		b->turn = -1;
		if (!checkValidBoard(b)) {
			free(b);
			return NULL;
		}

		int emptycount = 0;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			emptycount += (boardString[i] == EMPTY);
		}

		b->emptycount = emptycount;
		b->winner = checkwinInit(b);

		return b;
	}
	else {
		return NULL;
	}
}

void deleteBoard(Board *board) {
	if (board != NULL) {
		free(board);
	}
}

bool checkString(char *boardstr) {
	if (strlen(boardstr) != BOARD_SIZE)
		return false;
	else {
		// checks if contains only valid characters
		for (int i = 0; i < BOARD_SIZE; ++i) {
			if (boardstr[i] != PIECE_1 && boardstr[i] != PIECE_2 && boardstr[i] != EMPTY) {
				return false;
			}
		}
		return true;
	}
}

char getWinner(Board *board)
{
	if (board != NULL)
		return board->winner;
	else
		return INVALID_CHAR;
}


char checkHorizontal(Board *board, int col, int row, char c)
{
	int leftbound = MAX(col - (CONNECT_LEN - 1), 0);
	int rightbound = MIN(col + (CONNECT_LEN - 1), BOARD_WIDTH - 1);

	// checks for any 4 in a row
	int count = 0;
	for (int i = leftbound; i <= rightbound; ++i) {
		if (fastget(board, i, row) != c) {
			count = 0;
		}
		else if(++count == CONNECT_LEN) {
			return c;
		}
	}
	return INCOMPLETE;
}

char checkVertical(Board *board, int col, int row, char c)
{
	int topbound = MIN(row + (CONNECT_LEN - 1), BOARD_HEIGHT - 1);
	int bottombound = MAX(0, row - (CONNECT_LEN - 1));

	// check for any 4 in a col
	int count = 0;
	for (int i = bottombound; i <= topbound; ++i)
	{
		if (fastget(board, col, i) != c) {
			count = 0;
		}
		else if (++count == CONNECT_LEN) {
			return c;
		}
	}
	return INCOMPLETE;
}

char checkDiagonals(Board *board, int col, int row, char c)
{
	int topbound = MIN(row + (CONNECT_LEN - 1), BOARD_HEIGHT - 1);
	int bottombound = MAX(0, row - (CONNECT_LEN - 1));
	int leftbound = MAX(col - (CONNECT_LEN - 1), 0);
	int rightbound = MIN(col + (CONNECT_LEN - 1), BOARD_WIDTH - 1);
	int difftop = topbound - row;
	int diffbot = row - bottombound;
	int diffleft = col - leftbound;
	int diffright = rightbound - col;

	// bottomleft -> topright
	int leftdiagdiff = MIN(diffleft, diffbot);
	int rightdiagdiff = MIN(difftop, diffright);
	int count = 0;
	for (int i = -leftdiagdiff; i <= rightdiagdiff; ++i) {
		if (fastget(board, col + i, row + i) != c) {
			count = 0;
		}
		else if (++count == CONNECT_LEN) {
			return c;
		}
	}

	// topleft -> bottomright
	leftdiagdiff = MIN(diffleft, difftop);
	rightdiagdiff = MIN(diffright, diffbot);
	count = 0;
	for (int i = -leftdiagdiff; i <= rightdiagdiff; ++i) {
		if (fastget(board, col + i, row - i) != c) {
			count = 0;
		}
		else if (++count == CONNECT_LEN) {
			return c;
		}
	}

	return INCOMPLETE;
}

char checkwin(Board *board, int col, int row)
{
	char c = fastget(board, col, row);
	if (
			checkHorizontal(board, col, row, c) != INCOMPLETE ||
			checkVertical(board, col, row, c) != INCOMPLETE ||
			checkDiagonals(board, col, row, c) != INCOMPLETE) {
		return c;
	}
	else if (board->emptycount == 0) {
		return TIE;
	}
	else {
		return INCOMPLETE;
	}
}

char checkwinInit(Board *board)
{
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			if (fastget(board, j, i) == EMPTY) {
				continue;
			}

			char result = checkwin(board, j, i);
			if (result != INCOMPLETE) {
				return result;
			}
		}
	}
	return INCOMPLETE;
}

// TODO
Board *copyBoard(Board *board)
{
	board = NULL;
	return board;
}

void displayBoard(Board *board)
{
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			printf("%c ", board->board[i * BOARD_WIDTH + j]);
		}
		printf("\n");
	}
}
