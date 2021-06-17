#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "commandline.h"

void cmd_new(Board **b);
void cmd_help();
void cmd_disp(Board *b, Gamestate s);

void cmd_run()
{
	// game variables and configurations

	// initialize Board to something random so it points to somewhere already.
	// the data it contains is complete garbage as of right now.
	Board *b = (Board *) malloc(sizeof(Board));
	Gamestate state = NOT_INITIALIZED;

	// command string variables
	size_t sizeAlloc = 20;
	char *cmdstr = (char *) malloc(sizeof(char) * sizeAlloc);

	if (cmdstr == NULL) {
		perror("Unable to allocate memory for command\n");
		exit(1);
	}

	do {
		getline(&cmdstr, &sizeAlloc, stdin);

		// NEW
		if (strcmp(cmdstr, NEW) == 0) {
			cmd_new(&b);
			state = INITIALIZED;
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

		else {
			printf("Invalid command\n");
		}
	}
	while (1);
}

void cmd_new(Board **b)
{
	if (*b != NULL) {
		deleteBoard(*b);
	}

	*b = initBoard(NEWBOARD);
	if (*b == NULL) {
		perror("Unable to initialize board\n");
		exit(1);
	}
	printf("Initialized new board\n");
}


void cmd_help()
{
	printf("commands available:\n");
}

void cmd_disp(Board *b, Gamestate s)
{
	if (s != NOT_INITIALIZED)
		displayBoard(b);
	else
		printf("Board not initialized\n");
}
