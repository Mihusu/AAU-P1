#ifndef P1_TEST_FILTER_TEST_H
#define P1_TEST_FILTER_TEST_H

#include "CuTest.h"

void test_is_word_match_true(CuTest *tc);
void test_is_word_match_false(CuTest *tc);
void test_is_word_match_fails(CuTest *tc);
void test_CV_Density(CuTest *tc);
void test_Inclusion(CuTest *tc);

CuSuite *filter_get_suite();

#endif  // P1_TEST_FILTER_TEST_H
