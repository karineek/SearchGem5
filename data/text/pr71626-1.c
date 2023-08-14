// Modification timestamp: 2023-08-14 15:51:21
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr71626-1.c
/* PR middle-end/71626 */

typedef __INTPTR_TYPE__ V __attribute__((__vector_size__(sizeof (__INTPTR_TYPE__))));

__attribute__((noinline, noclone)) V
foo ()
{
  V v = { (__INTPTR_TYPE__) foo };
  return v;
}

int
main ()
{
  V v = foo ();
  if (v[0] != (__INTPTR_TYPE__) foo)
    __builtin_abort ();
  return 0;
}
