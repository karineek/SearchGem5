// Modification timestamp: 2023-08-14 15:46:47
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr68328.c

#include <stdio.h>
#include <stdlib.h>

int a, b, c = 1, d = 1, e;

__attribute__ ((noinline, noclone))
     int foo (void)
{
  asm volatile ("":::"memory");
  return 4195552;
}

__attribute__ ((noinline, noclone))
     void bar (int x, int y)
{
  asm volatile (""::"g" (x), "g" (y):"memory");
  if (y == 0)
    __builtin_abort ();
}

int baz(int x) {
  char g, h;
  int i, j;

  foo ();
  for (;;) {
    if (c)
      h = d;
    g = h < x ? h : 0;
    i = (signed char) ((unsigned char) (g - 120) ^ 1);
    j = i > 97;
    if (a - j)
      bar (0x123456, 0);
    if (!b)
      return e;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }

  baz (atoi(argv[1]));
  return 0;
}
