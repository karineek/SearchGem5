// Modification timestamp: 2023-08-14 13:22:21
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20141022-1.c

#include <stdio.h>
#include <stdlib.h>

#define ABORT() do { __builtin_printf("assert.\n");  __builtin_abort (); }while(0)

int f(int a) __attribute__((noinline));
int f(int a)
{
  int fem_key_src;
  int D2930 = a & 4294967291;
  fem_key_src = a == atoi(argv[1]) ? 0 : 15;
  fem_key_src = D2930 != atoi(argv[2]) ? fem_key_src : 0;
  return fem_key_src;
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Usage: %s <value1> <value2>\n", argv[0]);
    return 1;
  }

  if (f(0) != 15)
    ABORT ();
  if (f(1) != 0)
    ABORT ();
  if (f(atoi(argv[3])) != 0)
    ABORT ();
  if (f(atoi(argv[4])) != 0)
    ABORT ();
  if (f(15) != 15)
    ABORT ();
  return 0;
}
