#include <stdio.h>
#include <assert.h>

int rotate_left(unsigned x, int n) {
    unsigned w = 32;
    unsigned mask = (~0) << (w - n);
    return ((x & mask) >> (w - n)) | (x << n);
}

int main(int argc, char* argv[]) {
    assert(rotate_left(0x12345678, 4) == 0x23456781);
    assert(rotate_left(0x12345678, 20) == 0x67812345);
    return 0;
}
