// Modification timestamp: 2023-08-14 15:18:50
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr49644.c
/* PR c/49644 */

extern void abort (void);

int
main ()
{
  _Complex double a[12], *c = a, s = 3.0 + 1.0i;
  double b[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }, *d = b;
  int i;
  for (i = 0; i < 6; i++)
    *c++ = *d++ * s;
  if (c != a + 6 || d != b + 6)
    abort ();
  return 0;
}
