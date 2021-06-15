#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define BOARD_STRING_SIZE BOARD_WIDTH * BOARD_HEIGHT + 1

#define PIECE_1 'O'
#define PIECE_2 'X'
#define EMPTY '_'

typedef enum Winner {
	PLAYER1,
	PLAYER2,
	TIE,
	INCOMPLETE
} Winner;

// null terminated array so +1 length
// the board is indexed by COLUMNS, so therefore,
// _ O _
// _ O X = [ O _ _ X O O X X _ ]
// O X X
// Where O is Player1 piece, X is Player2 piece, _ is empty
typedef struct Board {
	char board[BOARD_STRING_SIZE];
	bool isValid;
} Board;

void add(Board *board, char piece, int position);
char checkwin(Board *board);
bool checkValidBoard(Board *board);
char get(Board *board, int column, int row);
#endif
