#ifndef TEST_BOARDS_H
#define TEST_BOARDS_H

#include "board.h"

#define EMPTYSTR \
	"_______" \
	"_______" \
	"_______" \
	"_______" \
	"_______" \
	"_______"

#define EMPTY1STR \
	"_______" \
	"_______" \
	"_______" \
	"_______" \
	"_______" \
	"_____O_"

#define VALID1STR \
	"______X" \
	"______O" \
	"____O_X" \
	"_OXXX_O" \
	"_OXOO_X" \
	"OXOOXXO"

#define VALID2STR \
	"______X" \
	"______O" \
	"____O_X" \
	"_OXXX_O" \
	"XOXOO_X" \
	"OXOOXXO"

#define VALID3STR \
	"______X" \
	"______O" \
	"____O_X" \
	"OOXXX_O" \
	"XOXOO_X" \
	"OXOOXXO"

#define VALID4STR \
	"______X" \
	"______O" \
	"X___O_X" \
	"OOXXX_O" \
	"XOXOO_X" \
	"OXOOXXO"

#define VALID5STR \
	"______X" \
	"______O" \
	"X___O_X" \
	"OOXXX_O" \
	"XOXOOOX" \
	"OXOOXXO"

#define XWINSTR \
	"______X" \
	"______O" \
	"X___O_X" \
	"OOXXXXO" \
	"XOXOOOX" \
	"OXOOXXO"

#define WINVERT \
	"_______" \
	"_______" \
	"_O_____" \
	"XO_____" \
	"XO_____" \
	"XO_____"

#define WINDIAG1 \
	"_______" \
	"_______" \
	"_O_X___" \
	"_OXO___" \
	"_XOX___" \
	"XOXO___"

#define WINDIAG2 \
	"_______" \
	"_O_____" \
	"_OOOX__" \
	"_OXOX__" \
	"_XOXOO_" \
	"XOXOXX_"

#define INVALID1STR \
	"_______" \
	"_______" \
	"___O___" \
	"_______" \
	"_______" \
	"_______"

#endif
