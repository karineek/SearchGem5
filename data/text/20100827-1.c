// Modification timestamp: 2023-08-14 13:18:39
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20100827-1.c
extern void abort (void);
int __attribute__((noinline,noclone))
foo (char *p)
{
  int h = 0;
  do
    {
      if (*p == '\0')
	break;
      ++h;
      if (p == 0)
	abort ();
      ++p;
    }
  while (1);
  return h;
}
int main()
{
  if (foo("a") != 1)
    abort ();
  return 0;
}
