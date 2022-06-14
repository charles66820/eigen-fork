#define VERBOSE false

#include "testUtil.h"
#include "pset1Test.h"
#include "pzeroTest.h"
#include "ploadTest.h"
#include "ploaduTest.h"
#include "paddTest.h"
#include "psubTest.h"
#include "pnegateTest.h"
#include "pmulTest.h"
#include "pdivTest.h"

int main() {
  pset1Tests();
  pzeroTests();
  ploadTests();
  ploaduTests();
  paddTests();
  psubTests();
  pnegateTests();
  pmulTests();
  pdivTests();
}
