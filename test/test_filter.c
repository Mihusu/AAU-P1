#include "CuTest.h"
#include "../src/cv-gen.c"

void test_is_word_match_true(CuTest *tc){
    char* in1 = strdup("streng");
    char* in2 = strdup("streng");
    int actual = is_word_match(in1, in2);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test_is_word_match_false(CuTest *tc){
    char* in1 = strdup("streng");
    char* in2 = strdup("char_array");
    int actual = is_word_match(in1, in2);
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

void test_is_word_match_fails(CuTest *tc){
    char* in1 = strdup("streng");
    char* in2 = strdup("Streng");
    int actual = is_word_match(in1, in2);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

CuSuite* cv_gen_get_suite(){
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_is_word_match_true);
    SUITE_ADD_TEST(suite, test_is_word_match_false);
    SUITE_ADD_TEST(suite, test_is_word_match_fails);
    return suite;
}
