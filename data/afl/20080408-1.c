// Modification timestamp: 2023-08-14 13:13:33
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20080408-1.c

#include <stdio.h>
#include <stdlib.h>

extern void abort(void);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }

  short ssi = atoi(argv[1]);
  unsigned short usi = atoi(argv[2]);
  int fail = !(ssi < usi);
  if (fail)
    abort();
  return 0;
}
