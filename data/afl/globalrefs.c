// Modification timestamp: 2023-08-14 17:35:48
// Original Source: https://github.com/llvm/llvm-test-suite/blob/156ba07a5c779f6b838dac832a25cf7691898288/SingleSource/Regression/C//globalrefs.c

#include <stdio.h>

#define __STDC_LIMIT_MACROS 1
#include <inttypes.h>

struct test {
  int A;
  struct { unsigned X; unsigned Y; } S;
  int B;
  struct test* next;
};

struct test  TestArray[10];
struct test  Test1;

/* Create global symbolic constants from the addresses of the above globals */

struct test* TestArrayPtr = &TestArray[3];
long*        Aptr         = &Test1.A;
unsigned*    Yptr         = &Test1.S.Y;
struct test** NextPtr     = &Test1.next;

void printdiff(void* p1, void* p2) {
  printf(" %d", (int)((unsigned long) p1 - (unsigned long) p2));
}

int main(int argc, char** argv) {
  if (argc != 1) {
    printf("Usage: %s\n", argv[0]);
    return 1;
  }

  unsigned long diff1, diff2, diff3, diff4;

  printdiff(&Test1.S.Y, &Test1.A);
  printdiff(&Test1.next, &Test1.S.Y);
  printf("\n");

  diff1 = (unsigned long) &TestArray[3] - (unsigned long) TestArray;
  diff3 = (unsigned long) &Test1.S.Y - (unsigned long) &Test1.A;
  diff4 = (unsigned long) &Test1.next - (unsigned long) &Test1.S.Y;

  if (diff1 != (diff1 / sizeof(*TestArray)) * sizeof(*TestArray))
    return 1;
  printf("&TestArray[3] - TestArray = 0x%lx\n", diff1 / sizeof(*TestArray));
  printf("Xptr - Aptr          = 0x%lx\n", diff3);
  printf("NextPtr - Xptr       = 0x%lx\n\n", diff4);

  diff1 = (unsigned long) TestArrayPtr - (unsigned long) TestArray;
  diff3 = (unsigned long) Yptr - (unsigned long) Aptr;
  diff4 = (unsigned long) NextPtr - (unsigned long) Yptr;

  if (diff1 != (diff1 / sizeof(*TestArray)) * sizeof(*TestArray))
    return 1;
  printf("&TestArray[3] - TestArray = 0x%lx\n", diff1 / sizeof(*TestArray));
  printf("Xptr - Aptr          = 0x%lx\n", diff3);
  printf("NextPtr - Xptr       = 0x%lx\n\n", diff4);

  return 0;
}
