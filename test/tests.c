#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board_suite.h"

int main(void)
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
  	if (CUE_SUCCESS != CU_initialize_registry())
    	return CU_get_error();

  	/* add a suite to the registry */
  	pSuite = CU_add_suite("Suite Board", init_suite_board, clean_suite_board);
  	if (pSuite == NULL)
	{
    	CU_cleanup_registry();
    	return CU_get_error();
  	}

	/* Adds tests to suite board. */
	if ((CU_add_test(pSuite, "checkValidBoard", test_checkValidBoard) == NULL))
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
