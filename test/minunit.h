/*
 * Copyright (c) 2012 David Siñuela Pastor, siu.4coders@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __MINUNIT_H__
#define __MINUNIT_H__

#ifdef __cplusplus
	extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>			
#include <string.h>
#include "minunit_config.h"

/*  Misc. counters */
extern int minunit_run;
extern int minunit_assert;
extern int minunit_fail;

static int minunit_status = 0;

/*  Test setup and teardown function pointers */
static void (*minunit_setup)(void) = NULL;
static void (*minunit_teardown)(void) = NULL;

/**
 * @brief      Helper for defining test function
 * @param      method_name  The method name
 */
#define MU_TEST(method_name) static void method_name(void)

/**
 * @brief      Helper for defining a suite
 * @param      method_name  The method name
 */
#define MU_TEST_SUITE(suite_name) void suite_name(void)

/**
 * @brief      Declares the extern variables that store information about test
 * @note 	   This should be called only once generally from the main test function
 */
#define MU_INIT() \
	int minunit_run = 0;\
	int minunit_assert = 0;\
	int minunit_fail = 0;\

/**
 * @brief      Protects the macro insides form the outside world
 * @param      block  The block to be in separate scope
 */
#define MU__SAFE_BLOCK(block) do {\
	block\
} while(0)

/**
 * @brief      Run a suite (collection of tests)
 * @param      suite_name  The suite name (should be void f(void))
 */
#define MU_RUN_SUITE(suite_name) MU__SAFE_BLOCK(\
	MU_PRINTF("\r\n");\
	(suite_name)();\
	minunit_setup = NULL;\
	minunit_teardown = NULL;\
)

/**
 * @brief      Run multiple suite (collection of tests)
 * @param      ...  List of suites each one as a argument
 */
#define MU_RUN_SUITES(...) do {\
    static void (*mu_suites[])(void) = {__VA_ARGS__};\
    for (uint32_t mu_i = 0; mu_i < sizeof(mu_suites)/sizeof(void(*)(void)); ++mu_i)\
    {\
        mu_suites[mu_i]();\
    }\
} while(0)

/**
 * @brief      Defines functions that will run before and after each test in suite
 * @param      setup_fun     The setup fun
 * @param      teardown_fun  The teardown fun
 */
#define MU_SUITE_CONFIGURE(setup_fun, teardown_fun) MU__SAFE_BLOCK(\
	minunit_setup = (setup_fun);\
	minunit_teardown = (teardown_fun);\
)

/**
 * @brief      Run a function as test
 * @param      test  The test function (should be void f(void))
 */
#define MU_RUN_TEST(test) MU__SAFE_BLOCK(\
	if (minunit_setup) {(*minunit_setup)();}\
	minunit_status = 0;\
	MU_PRINTF("\r\n");\
	MU_PRINTF("[%s.%s]\r\n" , __func__, #test);\
	(test)();\
	minunit_run++;\
	if (!minunit_status) { MU_PRINTF("pass = true\r\n"); }\
	if (minunit_teardown) { (*minunit_teardown)(); }\
)

/**
 * @brief      Print summary statistics about the test
 */
#define MU_REPORT() MU__SAFE_BLOCK(\
	MU_PRINTF("\r\n\r\n");\
	MU_PRINTF("[report]\r\n");\
	MU_PRINTF("tests = %d\r\n", minunit_run);\
	MU_PRINTF("assertions = %d\r\n", minunit_assert);\
	MU_PRINTF("failures = %d\r\n", minunit_fail);\
)

/**
 * @brief      [Private] Master assert
 * @param      name     Name of the assertion (will be printed on fail)
 * @param      test     The test to be preformed
 * @param      message  The format string, pretend this is a printf
 * @param      ...      Values for the pretend printf beforehand
 */
#define __MU_ASSERT(name, test, message, ...)  MU__SAFE_BLOCK(\
	minunit_assert++;\
	if (!(test)) {\
		MU_PRINTF("pass = false\r\n");\
		MU_PRINTF("fail = \"%s at %s:%d\"\r\n", name, __FILE__, __LINE__);\
		MU_PRINTF("reason = \""message"\"\r\n", __VA_ARGS__);\
		minunit_status = 1;\
		minunit_fail++;\
		return;\
	}\
)

/**
 * @brief      Check if value is truthy
 * @param      test     The value to be checked
 */
#define mu_check(test) __MU_ASSERT("mu_check", (test), "%s", "Test failed")

/**
 * @brief      Just fail
 * @param      message  The message that will be printed
 */
#define mu_fail(message) __MU_ASSERT("mu_fail", 0, "%s", (message))

/**
 * @brief      Check if the value is truthy print message on fail
 * @param      test     The value to be checked
 * @param      message  The message that will be printed on error
 */
#define mu_assert(test, message) __MU_ASSERT("mu_assert", (test), "%s", (message))

/**
 * @brief      Check two ints for equality
 * @param      expected  The expected value
 * @param      result    The computed value
 */
#define mu_assert_int_eq(size, expected, result) MU__SAFE_BLOCK(\
	int ##size ##_t expected_p = expected;\
	int ##size ##_t result_p = result;\
	__MU_ASSERT(\
		"mu_assert_int_eq",\
		(expected_p) == (result_p), \
		"%"PRId ##size" expected but was %"PRId ##size, \
		(expected_p), (result_p) \
	);\
)

#define mu_assert_int8_eq(expected, result) mu_assert_int_eq(8, expected, result);
#define mu_assert_int16_eq(expected, result) mu_assert_int_eq(16, expected, result);
#define mu_assert_int32_eq(expected, result) mu_assert_int_eq(32, expected, result);
#define mu_assert_int64_eq(expected, result) mu_assert_int_eq(64, expected, result);

/**
 * @brief      Check two unsigned ints for equality
 * @param      expected  The expected value
 * @param      result    The computed value
 */
#define mu_assert_uint_eq(size, expected, result) MU__SAFE_BLOCK(\
	uint ##size ##_t expected_p = expected;\
	uint ##size ##_t result_p = result;\
	__MU_ASSERT(\
		"mu_assert_uint_eq",\
		(expected_p) == (result_p), \
		"%"PRIu ##size" expected but was %"PRIu ##size, \
		(expected_p), (result_p) \
	);\
)

#define mu_assert_uint8_eq(expected, result) mu_assert_uint_eq(8, expected, result);
#define mu_assert_uint16_eq(expected, result) mu_assert_uint_eq(16, expected, result);
#define mu_assert_uint32_eq(expected, result) mu_assert_uint_eq(32, expected, result);
#define mu_assert_uint64_eq(expected, result) mu_assert_uint_eq(64, expected, result);

/**
 * @brief      Check if two floats are similar
 * @param      expected  The expected value
 * @param      result    The computed value
 * @param      epsilon   The maximum allowable difference between inputs
 */
#define mu_assert_float_close(expected, result, epsilon) MU__SAFE_BLOCK(\
	float diff = fabsf((expected) - (result)); \
	__MU_ASSERT( \
		"mu_assert_float_close",\
		diff < (epsilon), \
		"Difference of %f not within %f, %f !~= %f", \
		(double)diff, (double)(epsilon), \
		(double)(expected), (double)(result) \
	);\
)

/**
 * @brief      Check if two doubles are similar
 * @param      expected  The expected value
 * @param      result    The computed value
 * @param      epsilon   The maximum allowable difference between inputs
 */
#define mu_assert_double_close(expected, result, epsilon) MU__SAFE_BLOCK(\
	double diff = fabs((expected) - (result)); \
	__MU_ASSERT( \
		"mu_assert_double_close",\
		diff < (epsilon), \
		"Difference of %g not within %g, %g !~= %g", \
		diff, (epsilon), \
		(expected), (result) \
	);\
)

/**
 * @brief      Prompt user to verify something, they choose 'y' or 'n'
 * @param      message  The message to be showed to a user (generally a question)
 */
#define mu_confirm(message) MU__SAFE_BLOCK(\
	MU_PRINTF("prompt = \"%s\"\r\n", (message));\
	MU_PRINTF("# 'y' for yes, 'n' for no:\r\n");\
	fflush(stdout);\
	fflush(stdin);\
	char mu_input;\
	do { mu_input = MU_GETCHAR(); } while(mu_input != 'y' && mu_input != 'n');\
	MU_PRINTF("\r\n");\
	__MU_ASSERT("mu_confirm", mu_input == 'y', "%s", (message));\
)


#define mu_assert_string_eq(expected, result) MU__SAFE_BLOCK(\
	const char* minunit_tmp_e = expected;\
	const char* minunit_tmp_r = result;\
	minunit_assert++;\
	if (!minunit_tmp_e) {\
		minunit_tmp_e = "<null pointer>";\
	}\
	if (!minunit_tmp_r) {\
		minunit_tmp_r = "<null pointer>";\
	}\
        __MU_ASSERT(\
                "mu_assert_string_eq",\
                !strcmp(minunit_tmp_e, minunit_tmp_r), \
                "%s expected but was %s", \
                (minunit_tmp_e), (minunit_tmp_r) \
        );\
)


#ifdef __cplusplus
}
#endif

#endif /* __MINUNIT_H__ */
