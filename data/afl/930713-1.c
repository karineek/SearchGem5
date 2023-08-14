// Modification timestamp: 2023-08-14 13:35:13
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/930713-1.c

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char x;
} T;

T f(T s1)
{
  T s1a;
  s1a.x = 17;
  return s1a;
}

int main(int argc, char *argv[]) {
  T s1a, s1b;
  s1a.x = 13;
  s1b = f(s1a);
  if (s1a.x != 13 || s1b.x != 17)
    abort();
  exit(0);
}
