
// Modification timestamp: 2023-08-10 15:59:33
// Original Source: https://github.com/llvm/llvm-test-suite

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i, n = ((argc == 2) ? atoi(argv[1]) : 1);
    int *y = (int *) calloc(n, sizeof(int));
    for (i=0; i < n; i++)
      y[i] = i*i;
    printf("%d\n", y[n-1]);
    return(0);
}
