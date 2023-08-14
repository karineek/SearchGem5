// Modification timestamp: 2023-08-14 17:04:57
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/zero-struct-2.c
void abort (void);
int ii;
typedef struct {} raw_spinlock_t;
typedef struct {
  raw_spinlock_t raw_lock;
} spinlock_t;
raw_spinlock_t one_raw_spinlock (void)
{
  raw_spinlock_t raw_lock;
  ii++;
  return raw_lock;
}
int main(void)
{
  spinlock_t lock = (spinlock_t) { .raw_lock = one_raw_spinlock() };
  if (ii != 1)
    abort ();
  return 0;
}
