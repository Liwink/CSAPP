#include <stdio.h>
#include <assert.h>

int leftmost_one(unsigned x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x & ~(x >> 1);
}

int main(int argc, char* argv[]) {
    assert(leftmost_one(0x6600) == 0x4000);
    assert(leftmost_one(0x2600) == 0x2000);
    assert(leftmost_one(0x0) == 0x0);
    assert(leftmost_one(0x7FFFFFFF) == 0x40000000);
    assert(leftmost_one(0xFFFFFFFF) == 0x80000000);
    assert(leftmost_one(0x80000000) == 0x80000000);

    return 0;
}
