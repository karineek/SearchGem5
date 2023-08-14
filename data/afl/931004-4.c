// Modification timestamp: 2023-08-14 13:38:06
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/931004-4.c

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

struct tiny {
  short c;
};

void f(int n, ...) {
  struct tiny x;
  int i;

  va_list ap;
  va_start(ap, n);
  for (i = 0; i < n; i++) {
    x = va_arg(ap, struct tiny);
    if (x.c != i + 10)
      abort();
  }
  {
    long x = va_arg(ap, long);
    if (x != 123)
      abort();
  }
  va_end(ap);
}

int main(int argc, char *argv[]) {
  struct tiny x[3];
  x[0].c = argv[1][0];
  x[1].c = argv[2][0];
  x[2].c = argv[3][0];
  f(3, x[0], x[1], x[2], (long) 123);
  exit(0);
}
