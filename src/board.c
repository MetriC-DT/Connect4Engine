#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "board.h"

void add(Board *board, char piece, int position){

}

/*
 * Columns measured from the left 0 -> 6
 * Rows measured from the bottom 0 -> 5
 */
char get(Board *board, int col, int row) {
	if (board != NULL) {
		if (0 <= col && col < BOARD_WIDTH && 0 <= row && row < BOARD_HEIGHT) {
			int rowFromBottom = BOARD_HEIGHT - row - 1;
			return board->board[rowFromBottom * BOARD_WIDTH + col];
		}
		else {
			perror("Invalid get index");
			exit(1);
		}
	}
	else {
		perror("Attempted to get from invalid board");
		exit(1);
	}
}


bool stackCheck(Board *board) {
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		bool reachedStackTop = false;
		for (int j = 0; j < BOARD_HEIGHT ; ++j) {
			if (get(board, i, j) == EMPTY) {
				reachedStackTop = true;
			}
			else if (reachedStackTop) {
				return false;
			}
		}
	}
	return true;
}


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
