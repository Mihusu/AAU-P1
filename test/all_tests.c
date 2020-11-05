#include "all_tests.h"

#include <stdio.h>

#include "CuTest.h"
#include "filter_test.h"
#include "format_test.h"
#include "read_test.h"

void RunAllTests(void) {
    CuString* output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, filter_get_suite());
    CuSuiteAddSuite(suite, format_get_suite());
    CuSuiteAddSuite(suite, read_get_suite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

int main(void) { RunAllTests(); }
