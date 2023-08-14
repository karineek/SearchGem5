
// Modification timestamp: 2023-08-04 16:36:39
// Original Source: https://github.com/c-testsuite/c-testsuite/blob/master/tests/single-exec/2002-05-03-NotTest.c

#include <stdio.h>

void testBitWiseNot(int A, int B, int C, int D) {
  printf("Bitwise Not: %d %d %d %d\n", ~A, ~B, ~C, ~D);
}

void testBooleanNot(int A, int B, int C, int D) {
  printf("Boolean Not: %d %d %d %d %d %d\n",
         !(A > 0 && B > 0),
         !(A > 0 && C > 0),
         !(A > 0 && D > 0),
         !(B > 0 && C > 0),
         !(B > 0 && D > 0),
         !(C > 0 && D > 0));

}

int main() {
  testBitWiseNot(1, 2, -3, 5);
  testBooleanNot(1, 2, -3, 5);
  return 0;
}
