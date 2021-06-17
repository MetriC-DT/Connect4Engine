#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#define QUIT "quit\n"
#define NEW "new\n"
#define HELP "help\n"
#define DISP "disp\n"

typedef enum Gamestate {
	NOT_INITIALIZED,
	INITIALIZED,
	IN_PROGRESS
} Gamestate;

void cmd_run(void);

#endif
