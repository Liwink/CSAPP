#include <stdio.h>
#include <assert.h>
#include <limits.h>

int saturating_add(int x, int y) {
    int sum = x + y;
    unsigned w = sizeof(int) << 3;

    unsigned sum_first_bit = sum & 0x80000000;
    unsigned x_first_bit = x & 0x80000000;
    unsigned y_first_bit = y & 0x80000000;

    unsigned is_overflow = (!(x_first_bit ^ y_first_bit) && (x_first_bit ^ sum_first_bit));
    unsigned mask_overflow_a = (int) is_overflow << (w - 1) >> (w - 1);
    unsigned mask_overflow_b = ~(is_overflow << (w - 1));
    unsigned mask_negative_overflow = (int) (is_overflow && x_first_bit) << (w - 1) >> (w - 1);

    sum = ((sum | mask_overflow_a) & mask_overflow_b) ^ mask_negative_overflow;

    return sum;
}

int main(int argc, char* argv[]) {
    // printf("%d\n", saturating_add(INT_MAX, 1));
    // printf("%d\n", saturating_add(INT_MIN, -1));
    // printf("%d\n", saturating_add(12345, 67890));
    assert(saturating_add(INT_MAX, 1) == INT_MAX);
    assert(saturating_add(INT_MIN, -1) == INT_MIN);
    assert(saturating_add(12345, 67890) == 80235);
    return 0;
}
