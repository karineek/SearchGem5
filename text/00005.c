// Modification timestamp: 2023-08-02 17:15:00
// Original Source: https://github.com/c-testsuite/c-testsuite/blob/master/tests/single-exec/00005.c

int main() {
  int x;
  int *p;
  int **pp;

  x = 0;
  p = &x;
  pp = &p;

  if (*p)
    return 1;
  if (**pp)
    return 1;
  else
    **pp = 1;

  if (x)
    return 0;
  else
    return 1;
}
