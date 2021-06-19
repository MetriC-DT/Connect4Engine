#ifndef BOARD_SUITE_H
#define BOARD_SUITE_H

int init_suite_board(void);
int clean_suite_board(void);
void test_initboard(void);
void test_checkValidBoard(void);
void test_get(void);
void test_add(void);
void test_revert(void);
void test_stackHeight(void);
void test_add_fail(void);
void test_tie(void);
void test_checkwin(void);

#endif
