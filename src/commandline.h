#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#define QUIT "quit"
#define NEW "new"
#define HELP "help"
#define DISP "disp"

typedef enum Gamestate {
	NOT_INITIALIZED,
	INITIALIZED,
	IN_PROGRESS
} Gamestate;

void cmd_run(void);

#endif
