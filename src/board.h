#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define PIECE_1 'O'
#define PIECE_2 'X'
#define EMPTY '_'


// null terminated array so +1 length
// the board is indexed by COLUMNS, so therefore,
// _ O _
// _ O X = [ O _ _ X O O X X _ ]
// O X X
typedef struct Board {
	char board[BOARD_WIDTH * BOARD_HEIGHT + 1];
	bool isValid;
} Board;

void add(Board *board, char player, int position);
char checkwin(Board *board);
bool checkValidBoard(Board *board);
char get(Board *board, int column, int row);

#endif
