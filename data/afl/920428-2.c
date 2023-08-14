// Modification timestamp: 2023-08-14 13:26:03
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/920428-2.c

#include <stdio.h>
#include <stdlib.h>

int s(int i) {
    if (i > 0) {
        __label__ l1;
        int f(int i) {
            if (i == 2)
                goto l1;
            return 0;
        }
        return f(i);
        l1:;
    }
    return 1;
}

int x() {
    return s(0) == 1 && s(1) == 0 && s(2) == 1;
}

int main() {
    if (x() != 1)
        abort();
    exit(0);
}
