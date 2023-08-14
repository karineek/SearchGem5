// Modification timestamp: 2023-08-14 13:11:42
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20071202-1.c

#include <stdio.h>
#include <stdlib.h>

extern void abort(void);

struct T {
    int t;
    int r[8];
};

struct S {
    int a;
    int b;
    int c[6];
    struct T d;
};

__attribute__((noinline)) void foo(struct S *s) {
    *s = (struct S){s->b, s->a, {0, 0, 0, 0, 0, 0}, s->d};
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <value1> <value2>\n", argv[0]);
        return 1;
    }

    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);

    struct S s = {arg1, arg2, {1, 2, 3, 4, 5, 6}, {7, {8, 9, 10, 11, 12, 13, 14, 15}}};
    foo(&s);

    if (s.a != arg2 || s.b != arg1 ||
        s.c[0] || s.c[1] || s.c[2] || s.c[3] || s.c[4] || s.c[5])
        abort();

    if (s.d.t != 7 || s.d.r[0] != 8 || s.d.r[1] != 9 || s.d.r[2] != 10 ||
        s.d.r[3] != 11 || s.d.r[4] != 12 || s.d.r[5] != 13 ||
        s.d.r[6] != 14 || s.d.r[7] != 15)
        abort();

    return 0;
}
