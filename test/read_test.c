#include "read_test.h"

#include "CuTest.h"
#include "read.h"

CuSuite* read_get_suite() {
    CuSuite* suite = CuSuiteNew();
    return suite;
}
