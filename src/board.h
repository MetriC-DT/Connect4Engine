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
typedef struct Board {
	char board[BOARD_STRING_SIZE];
	bool isValid;
} Board;

void add(Board *board, char piece, int position);
char checkwin(Board *board);
bool checkValidBoard(Board *board);
char get(Board *board, int column, int row);

#endif
