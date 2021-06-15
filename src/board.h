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

typedef enum Status {
	BOARD_NULL,
	COLUMN_FULL,
	INVALID_INDEX,
	INVALID_PIECE,
	OK
} Status;

// null terminated array so +1 length
typedef struct Board {
	char board[BOARD_STRING_SIZE];
	int stackheight[BOARD_WIDTH];
	bool isValid;
} Board;

Status add(Board *board, char piece, int col);
char get(Board *board, int column, int row);
bool stackCheck(Board *board);
bool checkValidBoard(Board *board);
Board* initBoard(char *boardString);
void deleteBoard(Board *board);
bool checkStringSize(char *boardstr);
Winner checkwin(Board *board);

#endif
