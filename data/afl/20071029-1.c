// Modification timestamp: 2023-08-14 13:10:41
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20071029-1.c

#include <stdio.h>
#include <stdlib.h>

extern void exit(int);
extern void abort(void);

typedef union {
  struct {
    int f1, f2, f3, f4, f5, f6, f7, f8;
    long int f9, f10;
    int f11;
  } f;
  char s[56];
  long int a;
} T;

__attribute__((noinline))
void test(T *t) {
  static int i = 11;
  if (t->f.f1 != i++)
    abort();
  if (t->f.f2 || t->f.f3 || t->f.f4 || t->f.f5 || t->f.f6
      || t->f.f7 || t->f.f8 || t->f.f9 || t->f.f10 || t->f.f11)
    abort();
  if (i == 20)
    exit(0);
}

__attribute__((noinline))
void foo(int i) {
  T t;
again:
  t = (T){{++i, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  test(&t);
  goto again;
}

int main(void) {
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }
  
  T *t1, *t2;
  int cnt = atoi(argv[1]);
  t1 = (T *)0;

loop:
  t2 = t1;
  t1 = &(T){.f.f9 = cnt++};
  if (cnt < 3)
    goto loop;
  if (t1 != t2 || t1->f.f9 != 2)
    abort();
  foo(10);
  return 0;
}
