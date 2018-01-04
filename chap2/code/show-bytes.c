#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_short(short x) {
    printf("short\n");
    printf("%hd\n", x);
    show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
    printf("long\n");
    printf("%ld\n", x);
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_int(int x) {
    printf("int\n");
    printf("%d\n", x);
    // cast int * to byte_pointer
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    printf("float\n");
    printf("%f\n", x);
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_double(double x) {
    printf("double\n");
    show_bytes((byte_pointer) &x, sizeof(double));
}

void show_pointer(void *x) {
    printf("pointer\n");
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val) {
    int ival = val;
    short sval = (short) val;
    long lval = (long) val;
    float fval = (float) val;
    double dval = (double) val;
    int* pval = &val;

    show_int(ival);
    show_short(sval);
    show_long(lval);
    show_float(fval);
    show_double(dval);
    show_pointer(pval);
}

int main(int argc, char* argv[]) {
    int test_num = 16777217;

    test_show_bytes(test_num);
    return 0;
}

