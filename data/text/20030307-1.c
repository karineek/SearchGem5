// Modification timestamp: 2023-08-14 12:43:28
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/20030307-1.c
/* PR optimization/8726 */
/* Originator: Paul Eggert <eggert@twinsun.com> */

/* Verify that GCC doesn't miscompile tail calls on Sparc. */

extern void abort(void);

int fcntl_lock(int fd, int op, long long offset, long long count, int type);

int vfswrap_lock(char *fsp, int fd, int op, long long offset, long long count, int type)
{
  return fcntl_lock(fd, op, offset, count, type);
}

int fcntl_lock(int fd, int op, long long offset, long long count, int type)
{
  return type;
}

int main(void)
{
  if (vfswrap_lock (0, 1, 2, 3, 4, 5) != 5)
    abort();

  return 0;
}
