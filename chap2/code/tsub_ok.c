#include <stdio.h>
#include <assert.h>
#include <limits.h>

int tsub_ok(int x, int y) {
    int sub = x - y;

    unsigned pos_over = !(x & INT_MIN) && (y & INT_MIN) && (sub & INT_MIN);
    unsigned neg_over = (x & INT_MIN) && !(y & INT_MIN) && !(sub & INT_MIN);

    return !pos_over && !neg_over;
}

int main(int argc, char* argv[]) {
    assert(!tsub_ok(INT_MIN, 1));
    assert(!tsub_ok(INT_MAX, -1));
    assert(tsub_ok(INT_MAX, 1));
    assert(tsub_ok(INT_MIN, -1));
    return 0;
}
