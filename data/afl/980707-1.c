// Modification timestamp: 2023-08-14 13:51:09
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/980707-1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **
buildargv (char *input)
{
  static char *arglist[256];
  int numargs = 0;

  while (1)
  {
    while (*input == ' ')
      input++;
    if (*input == 0)
      break;
    arglist [numargs++] = input;
    while (*input != ' ' && *input != 0)
      input++;
    if (*input == 0)
      break;
    *(input++) = 0;
  }
  arglist [numargs] = NULL;
  return arglist;
}

int main(int argc, char *argv[]) {
  char **args;
  char input[256];
  int i;

  if (argc != 2) {
    printf("Usage: %s <input>\n", argv[0]);
    return 1;
  }

  strcpy(input, argv[1]);
  args = buildargv(input);

  if (strcmp (args[0], "a"))
    abort ();
  if (strcmp (args[1], "b"))
    abort ();
  if (args[2] != NULL)
    abort ();

  exit (0);
}
