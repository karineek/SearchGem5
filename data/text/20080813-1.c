// Modification timestamp: 2023-08-14 13:15:01
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20080813-1.c
/* PR middle-end/37103 */

extern void abort (void);

void
foo (unsigned short x)
{
  signed char y = -1;
  if (x == y)
    abort ();
}

void
bar (unsigned short x)
{
  unsigned char y = -1;
  if (x == y)
    abort ();
}

int
main (void)
{
  if (sizeof (int) == sizeof (short))
    return 0;
  foo (-1);
  if (sizeof (short) > 1)
    bar (-1);
  return 0;
}
