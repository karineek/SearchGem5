// Modification timestamp: 2023-08-14 15:42:15
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr65053-2.c

#include <stdio.h>
#include <stdlib.h>

int i;
unsigned int x;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }

  x = atoi(argv[1]);
  unsigned int n = x;
  unsigned int u = 32;
  if (n >= 32)
    __builtin_abort ();
  if (n != 0)
    u = n + 32;

  while (u != 32)
    {
      asm ("" : : "g" (u));
      u = 32;
      i = 1;
    }

  if (i)
    __builtin_abort ();
  return 0;
}

