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
#include "pset1frombitsTest.h"
#include "peven_maskTest.h"
#include "pload1Test.h"
#include "plsetTest.h"
#include "paddsubTest.h"
#include "ptrueTest.h"
#include "pandTest.h"
#include "porTest.h"
#include "pxorTest.h"
#include "pandnotTest.h"
#include "pcmp_leTest.h"
#include "pcmp_ltTest.h"
#include "pcmp_eqTest.h"
#include "pcmp_lt_or_nanTest.h"
#include "pminTest.h"
#include "pmaxTest.h"
#include "parithmetic_shift_rightTest.h"
#include "plogical_shift_rightTest.h"
#include "plogical_shift_leftTest.h"
#include "pabsTest.h"
#include "proundTest.h"
#include "printTest.h"
#include "pceilTest.h"
#include "pfloorTest.h"
#include "ploaddupTest.h"
#include "ploadquadTest.h"
#include "pgatherTest.h"
#include "pstoreTest.h"
#include "pstoreuTest.h"
#include "pscatterTest.h"
#include "pstore1Test.h"

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
  pset1frombitsTests();
  peven_maskTests();
  pload1Tests();
  plsetTests();
  paddsubTests();
  ptrueTests();
  pandTests();
  porTests();
  pxorTests();
  pandnotTests();
  pcmp_leTests();
  pcmp_ltTests();
  pcmp_eqTests();
  pcmp_lt_or_nanTests();
  pminTests();
  pmaxTests();
  parithmetic_shift_rightTests();
  plogical_shift_rightTests();
  plogical_shift_leftTests();
  pabsTests();
  proundTests();
  printTests();
  pceilTests();
  pfloorTests();
  ploaddupTests();
  ploadquadTests();
  pgatherTests();
  pstoreTests();
  pstoreuTests();
  pscatterTests();
  pstore1Tests();
}
