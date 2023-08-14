
// Modification timestamp: 2023-08-02 15:30:00
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/MultiSource/Benchmarks/llubenchmark/fftw-3.3.4/matrixTranspose.c

#include <stdio.h>
#include <stdlib.h>

typedef float fftw_real;

void complex_transpose(fftw_real *rA, fftw_real *iA, int n, int is, int js)
{
     int i, j;

     for (i = 1; i < n; ++i) {
       for (j = 0; j < i; ++j) {
         fftw_real ar, ai, br, bi;

         ar = rA[i * is + j * js];
         ai = iA[i * is + j * js];
         br = rA[j * is + i * js];
         bi = iA[j * is + i * js];

         rA[j * is + i * js] = ar;
         iA[j * is + i * js] = ai;
         rA[i * is + j * js] = br;
         iA[i * is + j * js] = bi;
       }
     }
}

extern int printf(const char *str, ...);

fftw_real A[2048];
int main(int argc, char **argv)
{
     int i;

     fftw_real sum = 0.0;
     for (i = 0; i < 2048; ++i) {
       A[i] = atoi(argv[1]);
       sum = sum + A[i];
     }
     printf("Checksum before = %lf\n", sum);

     for (i = 0; i < 10; ++i) {
       complex_transpose(A, A+1, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
     }

     sum = 0.0;
     for (i = 0; i < 2048; ++i)
       sum = sum + A[i];
     printf("Checksum  after = %lf\n", sum);

     return 0;
}
