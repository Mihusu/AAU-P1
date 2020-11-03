#include "CuTest.h"
#include "../src/filter.c"

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

void test_CV_Density(CuTest *tc){
    char *CV[PARA_AMOUNT][PARA_LENGTH] = {{"Jeg","har","en","gym","uddannelse"}, //testing, tb replace by read.c
                                            {"jeg","har","arbejdet","i","netto"},
                                            {"Jeg","er","god","til","C","prog"},
                                            {"Jeg","kan","finde","ud","af","machinelearning","og","statistik","og","sandsynlighedsteori"},
                                            {"Jeg","tager","en","Bsc","i","Software"},
                                            {"Erfaring","med","C","python","css","og","databaser"}};

    char *buzz[KEYWORD_LENGTH] = {"netto","gym","C","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","Bsc","Software"}; //testing, tb replace by read.c
    int length[PARA_AMOUNT] = {5,5,6,10,6,7}; //length of each individuel paragraph //testing, tb replace by read.c
    double density_of_Paragraph[PARA_AMOUNT];
    cv_Density(density_of_Paragraph,CV,buzz,length);
    printf("Test: 1: %lf 2: %lf 3: %lf 4: %lf 5: %lf 6: %lf \n", density_of_Paragraph[0],density_of_Paragraph[1],density_of_Paragraph[2],density_of_Paragraph[3],density_of_Paragraph[4],density_of_Paragraph[5]);
    printf("Expected: 1: 0.2 2: 0.2 3: 0.33 4: 0.3 5: 0.33 6: 0.57");
}

void test_Inclusion(CuTest *tc){
    char *CV[PARA_AMOUNT][PARA_LENGTH] = {{"Jeg","har","en","gym","uddannelse"}, //testing, tb replace by read.c
                                            {"jeg","har","arbejdet","i","netto"},
                                            {"Jeg","er","god","til","C","prog"},
                                            {"Jeg","kan","finde","ud","af","machinelearning","og","statistik","og","sandsynlighedsteori"},
                                            {"Jeg","tager","en","Bsc","i","Software"},
                                            {"Erfaring","med","C","python","css","og","databaser"}};

    char *buzz[KEYWORD_LENGTH] = {"netto","gym","C","prog","css","databaser","python","statistik","sandsynlighedsteori","machinelearning","Bsc","Software"}; //testing, tb replace by read.c
    int length[PARA_AMOUNT] = {5,5,6,10,6,7}; //length of each individuel paragraph //testing, tb replace by read.c
    double density_of_Paragraph[PARA_AMOUNT];
    cv_Density(density_of_Paragraph,CV,buzz,length);
    bool included_Paragraphs[PARA_AMOUNT] = {};
    inclusion(density_of_Paragraph,CV,length,included_Paragraphs);
}

CuSuite* cv_gen_get_suite(){
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_is_word_match_true);
    SUITE_ADD_TEST(suite, test_is_word_match_false);
    SUITE_ADD_TEST(suite, test_is_word_match_fails);
    SUITE_ADD_TEST(suite, test_CV_Density);
    SUITE_ADD_TEST(suite, test_Inclusion);
    return suite;
}
