#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board_suite.h"
#include "strategy_suite.h"

int main(void)
{
	CU_pSuite pSuiteBoard = NULL;
	CU_pSuite pSuiteStrategy = NULL;


	/* initialize the CUnit test registry */
  	if (CUE_SUCCESS != CU_initialize_registry())
    	return CU_get_error();

  	/* add a suite to the registry */
  	pSuiteBoard = CU_add_suite("Suite Board", init_suite_board, clean_suite_board);
	pSuiteStrategy = CU_add_suite("Suite Strategy", init_suite_strategy, clean_suite_strategy);

  	if (pSuiteBoard == NULL || pSuiteStrategy == NULL)
	{
    	CU_cleanup_registry();
    	return CU_get_error();
  	}

	/* Adds tests to suite board. */
	if (
			CU_add_test(pSuiteBoard, "test_init", test_initboard) == NULL ||
			CU_add_test(pSuiteBoard, "test_validBoard", test_checkValidBoard) == NULL ||
			CU_add_test(pSuiteBoard, "test_get", test_get) == NULL ||
			CU_add_test(pSuiteBoard, "test_add", test_add) == NULL ||
			CU_add_test(pSuiteBoard, "test_add_fail", test_add_fail) == NULL ||
			CU_add_test(pSuiteBoard, "test_checkwin", test_checkwin) == NULL ||
			CU_add_test(pSuiteBoard, "test_revert", test_revert) == NULL ||
			CU_add_test(pSuiteBoard, "test_tie", test_tie) == NULL ||
			CU_add_test(pSuiteBoard, "test_stackheight", test_stackHeight) == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Adds tests to suite strategy. */
	if (
			CU_add_test(pSuiteStrategy, "test_validmoves", test_ValidMoves) == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
