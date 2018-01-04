#include <stdio.h>
#include <assert.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
    unsigned w = 32;
    return (int) (word << (w - (bytenum << 3) - 8)) >> 24;
}

int main(int argc, char* argv[]) {
    assert(xbyte(0x6789ABCD, 0) == -51);
    assert(xbyte(0x6789ABCD, 2) == 0xFFFFFF89);
    return 0;
}
