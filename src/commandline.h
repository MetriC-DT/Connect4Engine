#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#define QUIT "quit"
#define NEW "new"
#define HELP "help"
#define DISP "disp"
#define REVERT "revert"
#define PUT "put "
#define GETMOVE "getmove"
#define EVAL "eval"
#define AVAILABLEMOVES "availablemoves"

typedef enum Gamestate {
	NOT_INITIALIZED,
	INITIALIZED,
	GAME_COMPLETE
} Gamestate;

void cmd_run(void);

#endif
