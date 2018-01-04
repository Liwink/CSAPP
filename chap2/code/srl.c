#include <stdio.h>
#include <assert.h>

unsigned srl(unsigned x, int k) {
    unsigned w = 8 * sizeof(int);
    unsigned xsra = (int) x >> k;
    return xsra & ~(~0 << (w - k));
}

int sra(int x, int k) {
    int xsrl = (unsigned) x >> k;
    unsigned w = 8 * sizeof(int);
    unsigned bias = (_Bool) (x & (1 << (w - 1)));
    return xsrl | (-bias << (w - k));
}

int main(int argc, char* argv[]) {
    int ival = -1;
    unsigned uval = (unsigned) ival;
    assert(srl(uval, 3) == uval >> 3);
    assert(sra(ival, 3) == ival >> 3);

    ival = 0x12345678;
    uval = (unsigned) ival;
    assert(srl(uval, 3) == uval >> 3);
    assert(sra(ival, 3) == ival >> 3);
}
