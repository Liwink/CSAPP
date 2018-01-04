#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    unsigned mask = 0xff << (i * 8);
    return (x & ~mask) | (b << i * 8);
}

int main(int argc, char* argv[]) {
    unsigned sample = 0x12345678;
    printf("%x\n", replace_byte(sample, 2, 0xab));
    printf("%x\n", replace_byte(sample, 0, 0xab));
}
