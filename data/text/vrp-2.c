// Modification timestamp: 2023-08-14 17:03:58
// Original Source: https://github.com/llvm/llvm-test-suite/blob/main/SingleSource/Regression/C/gcc-c-torture/execute/vrp-2.c
extern void abort ();
extern void exit (int);

int f (int a) {
	if (a != 2) {
		a = a > 0 ? a : -a;
		if (a == 2)
		  return 0;
		return 1;
	}
	return 1;
}

int main (int argc, char *argv[]) {
	if (f (-2))
		abort ();
	exit (0);
}
