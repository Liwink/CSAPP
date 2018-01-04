#include <stdio.h>
#include <assert.h>

int fits_bits(int x, int n) {
    unsigned val = (unsigned) x;
    unsigned w = sizeof(int) << 3;
    unsigned mask = ~0;
    return val <= (mask >> (w - n));
}

int main(int argc, char* argv[]) {
    assert(!fits_bits(8, 3));
    assert(fits_bits(8, 4));
    assert(fits_bits(8, 5));
    assert(fits_bits(0xFF, 8));
    return 0;
}
