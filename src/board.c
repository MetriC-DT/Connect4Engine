#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "board.h"

void add(Board *board, char player, int position){

}

char get(Board *board, int column, int row) {
	if (board != NULL && board->isValid) {
		return board->board[column * BOARD_HEIGHT + row];
	}
	else {
		perror("Attempted to get from invalid board");
		exit(1);
	}
}


bool stackCheck(Board *board) {
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		bool reachedStackTop = false;
		for (int j = 0; j < BOARD_HEIGHT; ++j) {
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
		return false;
	}
}
