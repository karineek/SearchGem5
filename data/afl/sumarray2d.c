// Modification timestamp: 2023-08-14 17:36:22
// Original Source: https://github.com/llvm/llvm-test-suite/blob/156ba07a5c779f6b838dac832a25cf7691898288/SingleSource/Regression/C//sumarray2d.c

#include <stdio.h>
#include <stdlib.h>

int SumArray(int Array[][100], unsigned int NumI, unsigned int NumJ) {
  unsigned i, j;
  int Result = 0;

  for (i = 0; i < NumI; i++)
    for (j = 0; j < NumJ; j++)
      Result += Array[i][j];

  return Result;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <NumI> <NumJ>\n", argv[0]);
    return 1;
  }

  unsigned int NumI = atoi(argv[1]);
  unsigned int NumJ = atoi(argv[2]);

  int Array[NumI][NumJ];
  unsigned int i, j;

  for (i = 0; i < NumI; i++)
    Array[i][i] = -i;

  for (i = 0; i < NumI; i++)
    for (j = 0; j < NumJ; j++)
      if (j != i)
        Array[i][j] = i+j;

  printf("Sum(Array[%d,%d] = %d\n", NumI, NumJ, SumArray(Array, NumI, NumJ));

  return 0;
}
