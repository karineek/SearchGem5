// Modification timestamp: 2023-08-03 18:00:30
// Original Source: https://github.com/c-testsuite/c-testsuite/blob/master/tests/single-exec/00032.c

int main() {
    int arr[2];
    int *p;

    arr[0] = 2;
    arr[1] = 3;
    p = &arr[0];
    if (*(p++) != 2)
        return 1;
    if (*(p++) != 3)
        return 2;

    p = &arr[1];
    if (*(p--) != 3)
        return 1;
    if (*(p--) != 2)
        return 2;

    p = &arr[0];
    if (*(++p) != 3)
        return 1;

    p = &arr[1];
    if (*(--p) != 2)
        return 1;

    return 0;
}
