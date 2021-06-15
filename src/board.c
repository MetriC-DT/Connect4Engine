#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

Status add(Board *board, char piece, int column){
	if (board == NULL || !board->isValid) {
		perror("board is invalid\n");
		return BOARD_INVALID;
	}
	else if (piece != PIECE_1 && piece != PIECE_2) {
		perror("Cannot place piece\n");
		return INVALID_PIECE;
	}
	else if (column < 0 || column >= BOARD_WIDTH) {
		perror("Invalid Column index\n");
		return INVALID_INDEX;
	}
	else if (board->stackheight[column] == BOARD_HEIGHT) {
		perror("Column is full\n");
		return COLUMN_FULL;
	}
	else {
		int rowFromTop = BOARD_HEIGHT - (++board->stackheight[column]);
		board->board[rowFromTop * BOARD_WIDTH + column] = piece;
		board->history[++board->turn] = column;
		return OK;
	}
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
	if (board != NULL) {
		if (0 <= col && col < BOARD_WIDTH && 0 <= row && row < BOARD_HEIGHT) {
			int rowFromTop = BOARD_HEIGHT - row - 1;
			return board->board[rowFromTop * BOARD_WIDTH + col];
		}
		else {
			perror("Invalid get index\n");
			exit(INVALID_INDEX);
		}
	}
	else {
		perror("Attempted to get from invalid board\n");
		exit(BOARD_INVALID);
	}
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
	if (boardString != NULL && checkStringSize(boardString)) {
		Board *b = (Board *) malloc(sizeof(Board));
		if (b == NULL) {
			perror("Memory not allocated for new board\n");
			return NULL;
		}
		strcpy(b->board, boardString);
		b->isValid = false;

		// begins at -1 in order to have zero indexed when the first element is added to history.
		b->turn = -1;
		if (!checkValidBoard(b)) {
			perror("BoardString is not valid!\n");
			free(b);
			return NULL;
		}
		return b;
	}
	else {
		perror("Invalid boardString\n");
		return NULL;
	}
}

void deleteBoard(Board *board) {
	if (board != NULL) {
		free(board);
	}
}

bool checkStringSize(char *boardstr) {
	return strlen(boardstr) == BOARD_STRING_SIZE - 1;
}
