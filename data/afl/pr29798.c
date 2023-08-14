// Modification timestamp: 2023-08-14 14:52:58
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr29798.c

#include <stdio.h>
#include <stdlib.h>

extern void abort();

int main(int argc, char *argv[]) {
  int i;
  double oldrho;
  double beta = 0.0;
  double work = atof(argv[1]);
  for (i = 1; i <= 2; i++) {
    double rho = work * work;
    if (i != 1)
      beta = rho / oldrho;
    if (beta == 1.0)
      abort();

    /* All targets even remotely likely to ever get supported
      use at least an even base, so there will never be any
      floating-point rounding. All computation in this test
      case is exact for even bases.  */
    work /= 2.0;
    oldrho = rho;
  }
  return 0;
}
