// Modification timestamp: 2023-08-14 16:54:27
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/user-printf.c

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __attribute__ ((format (printf, 1, 2), noipa))
user_print (const char *fmt, ...)
{
  va_list va;
  va_start (va, fmt);
  vfprintf (stdout, fmt, va);
  va_end (va);
}

int main(int argc, char *argv[]) {
  char *tmpfname = tmpnam(0);
  FILE *f = freopen(tmpfname, "w", stdout);
  if (!f) {
    perror("fopen for writing");
    return 1;
  }
  
  if (argc != 2) {
    printf("Usage: %s <value>\n", argv[0]);
    return 1;
  }
  
  user_print("1");
  user_print("%c", '2');
  user_print("%c%c", '3', '4');
  user_print("%s", "5");
  user_print("%s%s", "6", "7");
  user_print("%i", 8);
  user_print("%.1s\n", "9x");

  fclose(f);

  f = fopen(tmpfname, "r");
  if (!f) {
    perror("fopen for reading");
    remove(tmpfname);
    return 1;
  }

  char buf[12] = "";
  if (1 != fscanf(f, "%s", buf)) {
    perror("fscanf");
    fclose(f);
    remove(tmpfname);
    return 1;
  }

  fclose(f);
  remove(tmpfname);

  if (strcmp(buf, "123456789")) {
    abort();
  }

  return 0;
}

