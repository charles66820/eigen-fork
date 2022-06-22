#define VERBOSE false

#include "testUtil.h"
#include "PacketMathOldFun.h"

#include "PacketMathTests/pset1Test.h"
#include "PacketMathTests/pzeroTest.h"
#include "PacketMathTests/ploadTest.h"
#include "PacketMathTests/ploaduTest.h"
#include "PacketMathTests/paddTest.h"
#include "PacketMathTests/psubTest.h"
#include "PacketMathTests/pnegateTest.h"
#include "PacketMathTests/pmulTest.h"
#include "PacketMathTests/pdivTest.h"
#include "PacketMathTests/pset1frombitsTest.h"
#include "PacketMathTests/peven_maskTest.h"
#include "PacketMathTests/pload1Test.h"
#include "PacketMathTests/plsetTest.h"
#include "PacketMathTests/paddsubTest.h"
#include "PacketMathTests/ptrueTest.h"
#include "PacketMathTests/pandTest.h"
#include "PacketMathTests/porTest.h"
#include "PacketMathTests/pxorTest.h"
#include "PacketMathTests/pandnotTest.h"
#include "PacketMathTests/pcmp_leTest.h"
#include "PacketMathTests/pcmp_ltTest.h"
#include "PacketMathTests/pcmp_eqTest.h"
#include "PacketMathTests/pcmp_lt_or_nanTest.h"
#include "PacketMathTests/pminTest.h"
#include "PacketMathTests/pmaxTest.h"
#include "PacketMathTests/parithmetic_shift_rightTest.h"
#include "PacketMathTests/plogical_shift_rightTest.h"
#include "PacketMathTests/plogical_shift_leftTest.h"
#include "PacketMathTests/pabsTest.h"
#include "PacketMathTests/proundTest.h"
#include "PacketMathTests/printTest.h"
#include "PacketMathTests/pceilTest.h"
#include "PacketMathTests/pfloorTest.h"
#include "PacketMathTests/ploaddupTest.h"
#include "PacketMathTests/ploadquadTest.h"
#include "PacketMathTests/pgatherTest.h"
#include "PacketMathTests/pstoreTest.h"
#include "PacketMathTests/pstoreuTest.h"
#include "PacketMathTests/pscatterTest.h"
#include "PacketMathTests/pstore1Test.h"
#include "PacketMathTests/pfirstTest.h"
#include "PacketMathTests/preverseTest.h"

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
  pfirstTests();
  preverseTests();
}
