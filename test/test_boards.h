#ifndef TEST_BOARDS_H
#define TEST_BOARDS_H

#include "board.h"

char *EMPTYSTR = 
"_______"
"_______"
"_______"
"_______"
"_______"
"_______";

char *EMPTY1STR = 
"_______"
"_______"
"_______"
"_______"
"_______"
"_____O_";

char *VALID1STR =
"______X"
"______O"
"____O_X"
"_OXXX_O"
"_OXOO_X"
"OXOOXXO";

char *VALID2STR = 
"______X"
"______O"
"____O_X"
"_OXXX_O"
"XOXOO_X"
"OXOOXXO";

char *VALID3STR = 
"______X"
"______O"
"____O_X"
"OOXXX_O"
"XOXOO_X"
"OXOOXXO";

char *VALID4STR = 
"______X"
"______O"
"X___O_X"
"OOXXX_O"
"XOXOO_X"
"OXOOXXO";

char *VALID5STR = 
"______X"
"______O"
"X___O_X"
"OOXXX_O"
"XOXOOOX"
"OXOOXXO";

char *XWINSTR = 
"______X"
"______O"
"X___O_X"
"OOXXXXO"
"XOXOOOX"
"OXOOXXO";

char *INVALID1STR =
"_______"
"_______"
"___O___"
"_______"
"_______"
"_______";

#endif
