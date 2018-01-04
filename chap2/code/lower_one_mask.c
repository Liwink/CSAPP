#include <stdio.h>
#include <assert.h>

int lower_one_mask(int n){
    unsigned mask = ~0;
    return ~(mask << n);
}

int main(int argc, char* argv[]) {
    assert(lower_one_mask(6) == 0x3F);
    assert(lower_one_mask(17) == 0x1FFFF);
    return 0;
}
