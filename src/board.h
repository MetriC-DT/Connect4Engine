#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define BOARD_STRING_SIZE BOARD_WIDTH * BOARD_HEIGHT + 1
#define BOARD_SIZE BOARD_WIDTH * BOARD_HEIGHT

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
	BOARD_INVALID,
	COLUMN_FULL,
	INVALID_INDEX,
	INVALID_PIECE,
	OK
} Status;

typedef struct Board {
	bool isValid;
	char board[BOARD_STRING_SIZE];
	int stackheight[BOARD_WIDTH];
	int history[BOARD_SIZE];
	int turn;
} Board;

Status add(Board *board, char piece, int col);

// Obtains the piece at the given column
char get(Board *board, int column, int row);

// checks whether all the stacks are valid.
// Validity just checks the board for any
// floating pieces.
bool stackCheck(Board *board);

// checks whether a given board is valid.
// Uses stackCheck, checks Null, and string length.
bool checkValidBoard(Board *board);

// initializes a board from a boardString.
Board* initBoard(char *boardString);

// deletes board from memory.
void deleteBoard(Board *board);

// Checksh whether a given string is a valid board length.
bool checkStringSize(char *boardstr);

// Checks whether a given board has a completed game.
Winner checkwin(Board *board);

// creates a copy of a board. (allocates same board in new memory).
Board *copyBoard(Board *board);

#endif
