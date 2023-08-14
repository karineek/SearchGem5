// Modification timestamp: 2023-08-14 13:07:11
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20060929-1.c
/* PR c/29154 */

extern void abort (void);

void
foo (int **p, int *q)
{
  *(*p++)++ = *q++;
}

void
bar (int **p, int *q)
{
  **p = *q++;
  *(*p++)++;
}

void
baz (int **p, int *q)
{
  **p = *q++;
  (*p++)++;
}

int
main (void)
{
  int i = 42, j = 0;
  int *p = &i;
  foo (&p, &j);
  if (p - 1 != &i || j != 0 || i != 0)
    abort ();
  i = 43;
  p = &i;
  bar (&p, &j);
  if (p - 1 != &i || j != 0 || i != 0)
    abort ();
  i = 44;
  p = &i;
  baz (&p, &j);
  if (p - 1 != &i || j != 0 || i != 0)
    abort ();
  return 0;
}
