#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "commandline.h"
#include "strategy.h"

Board *cmd_new(Gamestate *s);
void cmd_help();
void cmd_disp(Board *b, Gamestate s);
void cmd_revert(Board *b, Gamestate s);
void cmd_put(Board *b, Gamestate s, int loc);
void cmd_eval(Board *b, Gamestate s);
void cmd_getmove(Board *b, Gamestate s);

void cmd_run()
{
	// game variables and configurations
	Board *b = NULL;
	Gamestate state = NOT_INITIALIZED;

	// command string variables
	size_t sizeAlloc = 20;
	char *cmdstr = (char *) malloc(sizeof(char) * sizeAlloc);

	if (cmdstr == NULL) {
		perror("Unable to allocate memory for command\n");
		exit(1);
	}

	while (1) {
		ssize_t len = getline(&cmdstr, &sizeAlloc, stdin);

		// replaces newline with null character.
		cmdstr[--len] = '\0';

		/********** COMMANDS ***********/
		// NEW
		if (strcmp(cmdstr, NEW) == 0) {
			deleteBoard(b);
			b = cmd_new(&state);
			state = INITIALIZED;
		}

		// REVERT
		else if (strcmp(cmdstr, REVERT) == 0) {
			cmd_revert(b, state);
		}

		// PUT
		else if (strncmp(cmdstr, PUT, strlen(PUT)) == 0) {
			// obtains the argument
			int start = strlen(PUT);
			char arg[len - start + 1];
			for (int i = 0; i < len - start; ++i) {
				arg[i] = cmdstr[start + i];
			}
			arg[len - start] = '\0';

			long loc = strtol(arg, NULL, 10);
			cmd_put(b, state, loc);
		}

		// GETMOVE
		else if (strcmp(cmdstr, GETMOVE) == 0) {
			cmd_getmove(b, state);
		}

		else if (strcmp(cmdstr, EVAL) == 0) {
			cmd_eval(b, state);
		}

		// HELP
		else if (strcmp(cmdstr, HELP) == 0) {
			cmd_help();
		}

		// DISP
		else if(strcmp(cmdstr, DISP) == 0) {
			cmd_disp(b, state);
		}

		// QUIT
		else if (strcmp(cmdstr, QUIT) == 0) {
			break;
		}

		// INVALID COMMAND
		else {
			printf("Invalid command\n");
		}
		/********** END COMMANDS ***********/

		// Debugging when game is over.
		// if (b != NULL && getWinner(b) != INCOMPLETE) {
		// 	printf("GAME IS OVER. Winner: %c\n", getWinner(b));
		// }
		// else {
		// 	displayBoard(b);
		// }
	}

	// frees all memory
	deleteBoard(b);
	free(cmdstr);
}

Board *cmd_new(Gamestate *s)
{
	Board *b = initBoard(NEWBOARD);
	if (b == NULL) {
		perror("Unable to initialize board\n");
		return NULL;
	}
	*s = INITIALIZED;
	printf("Initialized new board\n");
	return b;
}


void cmd_help()
{
	printf("commands available:\n");
	printf("* new\n");
	printf("* disp\n");
	printf("* put [0-6]\n");
	printf("* revert\n");
	printf("* getmove\n");
	printf("* eval\n");
	printf("* help\n");
	printf("* quit\n");
}


void cmd_disp(Board *b, Gamestate s)
{
	if (b == NULL || s != INITIALIZED)
		printf("Board invalid or not initialized\n");
	else
		displayBoard(b);
}

void cmd_revert(Board *b, Gamestate s)
{
	if (b == NULL || s != INITIALIZED || revert(b) != OK)
		printf("Unable to revert\n");
}

void cmd_put(Board *b, Gamestate s, int loc)
{
	if (b == NULL || s != INITIALIZED) {
		printf("Board invalid or not initialized\n");
		return;
	}
	Status status = add(b, loc);
	if (status != OK) {
		printf("Cannot Put. Reason: %s\n", STATUS_NAMES[status]);
	}
}

void cmd_getmove(Board *b, Gamestate s)
{
	if (b == NULL || s != INITIALIZED) {
		printf("Board invalid or not initialized\n");
		return;
	}
	else {
		printf("%d\n", strategyAlphaBeta(b).move);
	}
}

void cmd_eval(Board *b, Gamestate s)
{
	if (b == NULL || s != INITIALIZED) {
		printf("Board invalid or not initialized\n");
		return;
	}
	else {
		int multiplier = b->currentPlayer == PIECE_1 ? 1 : -1;
		printf("%d\n", multiplier * strategyAlphaBeta(b).value); 
	}
}
