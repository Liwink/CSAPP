#include <stdio.h>
#include <assert.h>

int leftmost_one(unsigned x) {
    unsigned long val = (unsigned long) x;
    val |= val >> 1;
    val |= val >> 2;
    val |= val >> 4;
    val |= val >> 8;
    val |= val >> 16;
    return (int) ((val + 1) >> 1);
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
