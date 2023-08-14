// Modification timestamp: 2023-08-14 14:12:51
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/builtin-types-compatible-p.c

#include <stdio.h>
#include <stdlib.h>

int i;
double d;
float rootbeer[__builtin_types_compatible_p(int, typeof(i))];

typedef enum { hot, dog, poo, bear } dingos;
typedef enum { janette, laura, amanda } cranberry;

typedef float same1;
typedef float same2;

int main(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  if (!(__builtin_types_compatible_p(int, const int)
	&& __builtin_types_compatible_p(typeof(hot), int)
	&& __builtin_types_compatible_p(typeof(hot), typeof(laura))
	&& __builtin_types_compatible_p(int[5], int[])
	&& __builtin_types_compatible_p(same1, same2)))
    abort();

  if (__builtin_types_compatible_p(char *, int)
      || __builtin_types_compatible_p(char *, const char *)
      || __builtin_types_compatible_p(long double, double)
      || __builtin_types_compatible_p(typeof(i), typeof(d))
      || __builtin_types_compatible_p(typeof(dingos), typeof(cranberry))
      || __builtin_types_compatible_p(char, int)
      || __builtin_types_compatible_p(char *, char **))
    abort();
  exit(0);
}

