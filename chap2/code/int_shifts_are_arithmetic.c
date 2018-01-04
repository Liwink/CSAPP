#include <stdio.h>
#include <assert.h>

int int_shifts_are_arithmetic() {
    int val = ~0;
    return val >> 1 == val;
}

int main(int argc, char* argv[]) {
    assert(int_shifts_are_arithmetic());
    return 0;
}
