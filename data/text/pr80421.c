// Modification timestamp: 2023-08-14 15:55:53
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr80421.c
/* PR middle-end/80421 */

__attribute__ ((noinline, noclone)) void
baz (const char *t, ...)
{
  asm volatile (""::"r" (t):"memory");
  if (*t == 'T')
    __builtin_abort ();
}

unsigned int
foo (char x)
{
  baz ("x %c\n", x);
  switch (x)
    {
    default:
      baz ("case default\n");
      if (x == 'D' || x == 'I')
	baz ("This should never be reached.\n");
      return 0;
    case 'D':
      baz ("case 'D'\n");
      return 0;
    case 'I':
      baz ("case 'I'\n");
      return 0;
    }
}

void
bar (void)
{
  int a = 2;
  int b = 5;
  char c[] = {
    2, 4, 1, 2, 5, 5, 2, 4, 4, 0, 0, 0, 0, 0, 0, 3, 4, 4, 2, 4,
    1, 2, 5, 5, 2, 4, 1, 0, 0, 0, 2, 4, 4, 3, 4, 3, 3, 5, 1, 3,
    5, 5, 2, 4, 4, 2, 4, 1, 3, 5, 3, 3, 5, 1, 3, 5, 1, 2, 4, 4,
    2, 4, 2, 3, 5, 1, 3, 5, 1, 3, 5, 5, 2, 4, 1, 2, 4, 2, 3, 5,
    3, 3, 5, 1, 3, 5, 5, 2, 4, 1, 2, 4, 1, 3, 5, 3, 3, 5, 1, 3,
    5, 5, 2, 4, 4, 2, 4, 1, 3, 5, 3, 3, 5, 1, 3, 5, 1, 2, 4, 1,
    2, 4, 2, 3, 5, 1, 3, 5, 1, 3, 5, 1, 2, 4, 1, 2, 4, 1, 3, 5,
    1, 3, 5, 1, 3, 5, 1, 2, 4, 4, 2, 4, 1, 3, 5, 1, 3, 5, 1, 3,
    5, 5, 2, 4, 4, 2, 4, 2, 3, 5, 3, 3, 5, 1, 3, 5, 5, 2, 4, 4,
    2, 4, 1, 3, 5, 3, 3, 5, 1, 3, 5, 1, 2, 5, 5, 2, 4, 2, 3, 5,
    1, 3, 4, 1, 3, 5, 1, 2, 5, 5, 2, 4, 1, 2, 5, 1, 3, 5, 3, 3,
    5, 1, 2, 5, 5, 2, 4, 2, 2, 5, 1, 3, 5, 3, 3, 5, 1, 2, 5, 1,
    2, 4, 1, 2, 5, 2, 3, 5, 1, 3, 5, 1, 2, 5, 1, 2, 4, 2, 2, 5,
    1, 3, 5, 1, 3, 5, 1, 2, 5, 5, 2, 4, 2, 2, 5, 2, 3, 5, 3, 3,
    5, 1, 2, 5, 5, 2, 4, 2, 2, 5, 2, 3, 5, 3, 3, 5, 1, 2, 5, 5,
    2, 4, 2, 2, 5, 1, 3, 5, 3, 3, 5, 1, 2, 5, 5, 2, 4, 2, 2, 5,
    1, 3, 5, 3, 3, 5, 1, 2, 5, 1, 2, 4, 1, 2, 5, 2, 3, 5, 1, 3,
    5, 1, 2, 5, 5, 2, 4, 2, 2, 5, 2, 3, 5, 3, 3, 5, 1, 2, 5, 5,
    2, 4, 1, 2, 5, 1, 3, 5, 3, 3, 5, 1, 2, 5, 5, 2, 4, 2, 2, 5,
    1, 3, 5, 3, 3, 5, 1, 2, 5, 5, 2, 4, 2, 2, 5, 1, 3, 5, 3, 3,
    5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  char *f = c + 390;
  int i, j, e, g, h;
  char k, l;
  i = 26;
  j = 25;
  k = l = 'M';
  h = 2;
  while (i > 0)
    {
      int x = i - a;
      x = x > 0 ? x : 0;
      x = j - x;
      g = x * 3 + h;
      switch (f[g])
	{
	case 1:
	  --i;
	  --j;
	  h = 2;
	  f -= b * 3;
	  k = 'M';
	  break;
	case 2:
	  --i;
	  h = 0;
	  f -= b * 3;
	  k = 'I';
	  break;
	case 3:
	  --i;
	  h = 2;
	  f -= b * 3;
	  k = 'I';
	  break;
	case 4:
	  --j;
	  h = 1;
	  k = 'D';
	  break;
	case 5:
	  --j;
	  h = 2;
	  k = 'D';
	  break;
	}
      if (k == l)
	++e;
      else
	{
	  foo (l);
	  l = k;
	}
    }
}

int
main ()
{
  char l = 'D';
  foo (l);
  bar ();
  return 0;
}
