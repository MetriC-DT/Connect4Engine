#ifndef TEST_BOARDS_H
#define TEST_BOARDS_H

#include "board.h"

Board emptyBoard = {
	"_______"
	"_______"
	"_______"
	"_______"
	"_______"
	"_______",
	false
};

Board valid1 = {
	"______X"
	"______X"
	"_OX_OOX"
	"OXOXOOO"
	"OOOXXXX"
	"OOOOOOO",
	false
};

Board invalid1 = {
	"_______"
	"_______"
	"___O___"
	"_______"
	"_______"
	"_______",
	false
};

#endif
