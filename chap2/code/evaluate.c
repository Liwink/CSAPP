#include <stdio.h>
#include <assert.h>

int condition_a(int x) {
    return x;
}

int condition_b(int x) {
    return ~x;
}

int condition_c(int x) {
    return x & 0xff;
}

int condition_d(int x) {
    return (~x >> ((sizeof(int) - 1) << 3)) & 0xff;
}

int main(int argc, char* argv[]) {
    int all_bit_one = ~0;
    int all_bit_zero = 0;

    assert(condition_a(all_bit_one));
    assert(!condition_b(all_bit_one));
    assert(condition_c(all_bit_one));
    assert(!condition_d(all_bit_one));

    assert(!condition_a(all_bit_zero));
    assert(condition_b(all_bit_zero));
    assert(!condition_c(all_bit_zero));
    assert(condition_d(all_bit_zero));

    int test_a = 0x1234ff;
    assert(condition_a(test_a));
    assert(condition_b(test_a));
    assert(condition_c(test_a));
    assert(condition_d(test_a));
}
