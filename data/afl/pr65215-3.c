// Modification timestamp: 2023-08-14 15:42:49
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr65215-3.c

#include <stdio.h>
#include <stdlib.h>

struct S { unsigned long long l1 : 24, l2 : 8, l3 : 32; };

static inline unsigned int
foo (unsigned int x)
{
  return (x >> 24) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000) | (x << 24);
}

__attribute__((noinline, noclone)) unsigned long long
bar (struct S *x)
{
  unsigned long long x1 = foo (((unsigned int) x->l1 << 8) | x->l2);
  unsigned long long x2 = foo (x->l3);
  return (x2 << 32) | x1;
}

int
main (int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }

  if (__CHAR_BIT__ != 8 || sizeof (unsigned int) != 4 || sizeof (unsigned long long) != 8)
    return 0;
  struct S s = { 0xdeadbeU, 0xefU, 0xfeedbea8U };
  unsigned long long l = bar (&s);
  if (foo (l >> 32) != s.l3
      || (foo (l) >> 8) != s.l1
      || (foo (l) & 0xff) != s.l2)
    __builtin_abort ();
  return 0;
}
