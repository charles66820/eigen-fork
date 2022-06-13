#define VERBOSE false

#include "testUtil.h"
#include "pset1Test.h"
#include "pzeroTest.h"
#include "ploadTest.h"
#include "ploaduTest.h"

int main() {
  pset1Tests();
  pzeroTests();
  ploadTests();
  ploaduTests();
}
