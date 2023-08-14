// Modification timestamp: 2023-08-14 15:12:11
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr43784.c
struct s {
  unsigned char a[256];
};
union u {
  struct { struct s b; int c; } d;
  struct { int c; struct s b; } e;
};

static union u v;
static struct s *p = &v.d.b;
static struct s *q = &v.e.b;

static struct s __attribute__((noinline)) rp(void)
{
  return *p;
}

static void qp(void)
{
  *q = rp();
}

int main()
{
  int i;
  for (i = 0; i < 256; i++)
    p->a[i] = i;
  qp();
  for (i = 0; i < 256; i++)
    if (q->a[i] != i)
      __builtin_abort();
  return 0;
}
