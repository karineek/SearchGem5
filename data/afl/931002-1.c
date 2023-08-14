// Modification timestamp: 2023-08-14 13:36:30
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/931002-1.c

#include <stdio.h>
#include <stdlib.h>

void f(void (*func)()) {
  func();
}

void t0() {
}

void t1() {
  f(t0);
}

void t2() {
  t1();
}

int main(int argc, char *argv[]) {
  t1();
  t1();
  t2();

  exit(0);
}
