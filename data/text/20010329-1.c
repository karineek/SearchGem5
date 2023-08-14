// Modification timestamp: 2023-08-14 11:58:23
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20010329-1.c
#include <limits.h>

int main (void)
{
  void *x = ((void *)((unsigned int)INT_MAX + 2));
  void *y = ((void *)((unsigned long)LONG_MAX + 2));
  if (x >= ((void *)((unsigned int)INT_MAX + 1))
      && x <= ((void *)((unsigned int)INT_MAX + 6))
      && y >= ((void *)((unsigned long)LONG_MAX + 1))
      && y <= ((void *)((unsigned long)LONG_MAX + 6)))
    exit (0);
  else
    abort ();
}
