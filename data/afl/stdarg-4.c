// Modification timestamp: 2023-08-14 16:13:02
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/stdarg-4.c

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void abort(void);

long x, y;

inline void __attribute__((always_inline))
f1i(va_list ap)
{
  x = va_arg(ap, long);
  x += va_arg(ap, long);
  x += va_arg(ap, long);
}

void f1(int i, ...)
{
  va_list ap;
  va_start(ap, i);
  f1i(ap);
  va_end(ap);
}

inline void __attribute__((always_inline))
f2i(va_list ap)
{
  y = va_arg(ap, int);
  y += va_arg(ap, long);
  y += va_arg(ap, long);
  f1i(ap);
}

void f2(int i, ...)
{
  va_list ap;
  va_start(ap, i);
  f2i(ap);
  va_end(ap);
}

long f3h(int i, long arg0, long arg1, long arg2, long arg3)
{
  return i + arg0 + arg1 + arg2 + arg3;
}

long f3(int i, ...)
{
  long t, arg0, arg1, arg2, arg3;
  va_list ap;

  va_start(ap, i);
  switch (i)
  {
  case 0:
    t = f3h(i, 0, 0, 0, 0);
    break;
  case 1:
    arg0 = va_arg(ap, long);
    t = f3h(i, arg0, 0, 0, 0);
    break;
  case 2:
    arg0 = va_arg(ap, long);
    arg1 = va_arg(ap, long);
    t = f3h(i, arg0, arg1, 0, 0);
    break;
  case 3:
    arg0 = va_arg(ap, long);
    arg1 = va_arg(ap, long);
    arg2 = va_arg(ap, long);
    t = f3h(i, arg0, arg1, arg2, 0);
    break;
  case 4:
    arg0 = va_arg(ap, long);
    arg1 = va_arg(ap, long);
    arg2 = va_arg(ap, long);
    arg3 = va_arg(ap, long);
    t = f3h(i, arg0, arg1, arg2, arg3);
    break;
  default:
    abort();
  }
  va_end(ap);

  return t;
}

void f4(int i, ...)
{
  va_list ap;

  va_start(ap, i);
  switch (i)
  {
  case 4:
    y = va_arg(ap, double);
    break;
  case 5:
    y = va_arg(ap, double);
    y += va_arg(ap, double);
    break;
  default:
    abort();
  }
  f1i(ap);
  va_end(ap);
}

int main(int argc, char *argv[])
{
  if (argc != 1)
  {
    printf("Usage: %s\n", argv[0]);
    return 1;
  }

  f1(3, 16L, 128L, 32L);
  if (x != 176L)
    abort();
  f2(6, 5, 7L, 18L, 19L, 17L, 64L);
  if (x != 100L || y != 30L)
    abort();
  if (f3(0) != 0)
    abort();
  if (f3(1, 18L) != 19L)
    abort();
  if (f3(2, 18L, 100L) != 120L)
    abort();
  if (f3(3, 18L, 100L, 300L) != 421L)
    abort();
  if (f3(4, 18L, 71L, 64L, 86L) != 243L)
    abort();
  f4(4, 6.0, 9.0, 16L, 18.0);
  if (x != 43L || y != 6L)
    abort();
  f4(5, 7.0, 21.0, 1.0, 17L, 126.0);
  if (x != 144L || y != 28L)
    abort();
  return 0;
}
