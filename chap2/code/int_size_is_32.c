#include <stdio.h>
#include <assert.h>

int int_size_is_32() {
    int set_msb = 1 << 31;
    return !(set_msb + set_msb);
}

int int_size_is_32_for_16() {
    unsigned int val = ~0;
    return val == 4294967295;
}

int main(int argc, char* argv[]) {
    assert(int_size_is_32());
    assert(int_size_is_32_for_16());
    return 0;
}
