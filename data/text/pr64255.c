// Modification timestamp: 2023-08-14 15:41:22
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr64255.c
/* PR rtl-optimization/64255 */

__attribute__((noinline, noclone)) void
bar (long i, unsigned long j)
{
  if (i != 1 || j != 1)
    __builtin_abort ();
}

__attribute__((noinline, noclone)) void
foo (long i)
{
  unsigned long j;

  if (!i)
    return;
  j = i >= 0 ? (unsigned long) i : - (unsigned long) i;
  if ((i >= 0 ? (unsigned long) i : - (unsigned long) i) != j)
    __builtin_abort ();
  bar (i, j);
}

int
main ()
{
  foo (1);
  return 0;
}
