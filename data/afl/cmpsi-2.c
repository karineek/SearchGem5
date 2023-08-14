// Modification timestamp: 2023-08-14 14:16:29
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/cmpsi-2.c

#include <stdio.h>
#include <stdlib.h>

#define F 140
#define T 13

int feq(int x, int y) {
  if (x == y)
    return T;
  else
    return F;
}

int fne(int x, int y) {
  if (x != y)
    return T;
  else
    return F;
}

int flt(int x, int y) {
  if (x < y)
    return T;
  else
    return F;
}

int fge(int x, int y) {
  if (x >= y)
    return T;
  else
    return F;
}

int fgt(int x, int y) {
  if (x > y)
    return T;
  else
    return F;
}

int fle(int x, int y) {
  if (x <= y)
    return T;
  else
    return F;
}

int fltu(unsigned int x, unsigned int y) {
  if (x < y)
    return T;
  else
    return F;
}

int fgeu(unsigned int x, unsigned int y) {
  if (x >= y)
    return T;
  else
    return F;
}

int fgtu(unsigned int x, unsigned int y) {
  if (x > y)
    return T;
  else
    return F;
}

int fleu(unsigned int x, unsigned int y) {
  if (x <= y)
    return T;
  else
    return F;
}

unsigned int args[] = {
  0L,
  1L,
  -1L,
  0x7fffffffL,
  0x80000000L,
  0x80000001L,
  0x1A3F2373L,
  0x93850E92L
};

int correct_results[] = {
  T, F, F, T, F, T, F, T, F, T,
  F, T, T, F, F, T, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, T, F, F, T, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, T, F, F, T, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, F, T, T, F, F, T, T, F,
  T, F, F, T, F, T, F, T, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, T, F, F, T, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, T, F, F, T, F, T, T, F,
  F, T, T, F, F, T, F, T, T, F,
  T, F, F, T, F, T, F, T, F, T,
  F, T, T, F, F, T, F, T, T, F,
  F, T, F, T, T, F, F, T, T, F,
  F, T, F, T, T, F, F, T, T, F,
  F, T, T, F, F, T, F, T, T, F,
  F, T, F, T, T, F, F, T, T, F,
  F, T, F, T, T, F, F, T, T, F,
  F, T, F, T, T, F, F, T, T, F,
  F, T, F, T, T, F, F, T, T, F,
  F, T, F, T, T, F, T, F, F, T,
  T, F, F, T, F, T, F, T, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, F, T, T, F, T, F, F, T,
  F, T, T, F, F, T, F, T, T, F,
  F, T, T, F, F, T, F, T, T, F,
  F, T, T, F, F, T, T, F, F, T,
  F, T, T, F, F, T, F, T, T, F,
  T, F, F, T, F, T, F, T, F, T,
  F, T, T, F, F, T, T, F, F, T,
  F, T, T, F, F, T, F, T, T, F,
  F, T, T, F, F, T, T, F, F, T,
  F, T, T, F, F, T, F, T, T, F,
  F, T, T, F, F, T, F, T, T, F,
  F, T, T, F, F, T, T, F, F, T,
  F, T, T, F, F, T, F, T, T, F,
  F, T, F, T, T, F, F, T, T, F,
  T, F, F, T, F, T, F, T, F, T
};

int main(void) {
  int i, j, *res = correct_results;

  for (i = 0; i < 8; i++) {
    unsigned int arg0 = args[i];
    for (j = 0; j < 8; j++) {
      unsigned int arg1 = args[j];

      if (feq(arg0, arg1) != *res++)
        abort();
      if (fne(arg0, arg1) != *res++)
        abort();
      if (flt(arg0, arg1) != *res++)
        abort();
      if (fge(arg0, arg1) != *res++)
        abort();
      if (fgt(arg0, arg1) != *res++)
        abort();
      if (fle(arg0, arg1) != *res++)
        abort();
      if (fltu(arg0, arg1) != *res++)
        abort();
      if (fgeu(arg0, arg1) != *res++)
        abort();
      if (fgtu(arg0, arg1) != *res++)
        abort();
      if (fleu(arg0, arg1) != *res++)
        abort();
    }
  }
  exit(0);
}
