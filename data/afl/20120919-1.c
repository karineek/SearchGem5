// Modification timestamp: 2023-08-14 13:21:06
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20120919-1.c

#include <stdio.h>
#include <stdlib.h>

double vd[2] = {1., 0.};
int vi[2] = {1234567890, 0};
double *pd = vd;
int *pi = vi;

extern void abort(void);

void init (int *n, int *dummy) __attribute__ ((noinline,noclone));

void init (int *n, int *dummy)
{
  if(0 == n) dummy[0] = 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }

  int dummy[1532];
  int i = -1, n = atoi(argv[1]), s = 0;
  init (&n, dummy);
  while (i < n) {
    if (i == 0) {
      if (pd[i] > 0) {
        if (pi[i] > 0) {
          s += pi[i];
        }
      }
      pd[i] = pi[i];
    }
    ++i;
  }
  if (s != 1234567890)
    abort ();
  return 0;
}
