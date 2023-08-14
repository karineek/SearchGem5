// Modification timestamp: 2023-08-14 14:08:00
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/bswap-2.c

#include <stdio.h>

typedef unsigned int uint32_t;

struct bitfield {
  unsigned char f0:7;
  unsigned char   :1;
  unsigned char f1:7;
  unsigned char   :1;
  unsigned char f2:7;
  unsigned char   :1;
  unsigned char f3:7;
};

struct ok {
  unsigned char f0;
  unsigned char f1;
  unsigned char f2;
  unsigned char f3;
};

union bf_or_uint32 {
  struct ok inval;
  struct bitfield bfval;
};

uint32_t partial_read_le32(union bf_or_uint32 in) {
  return in.bfval.f0 | (in.bfval.f1 << 8)
         | (in.bfval.f2 << 16) | (in.bfval.f3 << 24);
}

uint32_t partial_read_be32(union bf_or_uint32 in) {
  return in.bfval.f3 | (in.bfval.f2 << 8)
         | (in.bfval.f1 << 16) | (in.bfval.f0 << 24);
}

uint32_t fake_read_le32(char *x, char *y) {
  unsigned char c0, c1, c2, c3;

  c0 = x[0];
  c1 = x[1];
  *y = 1;
  c2 = x[2];
  c3 = x[3];
  return c0 | c1 << 8 | c2 << 16 | c3 << 24;
}

uint32_t fake_read_be32(char *x, char *y) {
  unsigned char c0, c1, c2, c3;

  c0 = x[0];
  c1 = x[1];
  *y = 1;
  c2 = x[2];
  c3 = x[3];
  return c3 | c2 << 8 | c1 << 16 | c0 << 24;
}

uint32_t incorrect_read_le32(char *x, char *y) {
  unsigned char c0, c1, c2, c3;

  c0 = x[0];
  c1 = x[1];
  c2 = x[2];
  c3 = x[3];
  *y = 1;
  return c0 | c1 << 8 | c2 << 16 | c3 << 24;
}

uint32_t incorrect_read_be32(char *x, char *y) {
  unsigned char c0, c1, c2, c3;

  c0 = x[0];
  c1 = x[1];
  c2 = x[2];
  c3 = x[3];
  *y = 1;
  return c3 | c2 << 8 | c1 << 16 | c0 << 24;
}

int main(int argc, char *argv[]) {
  union bf_or_uint32 bfin;
  uint32_t out;
  char cin[] = { 0x83, 0x85, 0x87, 0x89 };

  if (sizeof(uint32_t) * __CHAR_BIT__ != 32)
    return 0;
  bfin.inval = (struct ok) { 0x83, 0x85, 0x87, 0x89 };
  out = partial_read_le32(bfin);
  if (out == 0x89878583)
    __builtin_abort();
  bfin.inval = (struct ok) { 0x83, 0x85, 0x87, 0x89 };
  out = partial_read_be32(bfin);
  if (out == 0x83858789)
    __builtin_abort();
  out = fake_read_le32(cin, &cin[2]);
  if (out != 0x89018583)
    __builtin_abort();
  cin[2] = 0x87;
  out = fake_read_be32(cin, &cin[2]);
  if (out != 0x83850189)
    __builtin_abort();
  cin[2] = 0x87;
  out = incorrect_read_le32(cin, &cin[2]);
  if (out != 0x89878583)
    __builtin_abort();
  cin[2] = 0x87;
  out = incorrect_read_be32(cin, &cin[2]);
  if (out != 0x83858789)
    __builtin_abort();
  return 0;
}
