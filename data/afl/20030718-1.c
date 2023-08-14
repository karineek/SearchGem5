// Modification timestamp: 2023-08-14 12:47:46
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20030718-1.c

/* PR c/10320
   The function temp was not being emitted in a prerelease of 3.4 20030406.
   Contributed by pinskia@physics.uc.edu */

#include <stdio.h>

static inline void temp(int argc, char *argv[]);
int main(int argc, char *argv[]) {
        temp(argc, argv);
        return 0;
}
static void temp(int argc, char *argv[]) {}
