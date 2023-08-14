// Modification timestamp: 2023-08-14 14:55:54
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/pr34070-1.c

#include <stdio.h>
#include <stdlib.h>

extern void abort(void);

int f(unsigned int x) {
  return ((int)x) % 4;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }

  int result = f(atoi(argv[1]));
  if (result != -1) {
    abort();
  }
  return 0;
}
