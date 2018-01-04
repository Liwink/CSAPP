#include <stdio.h>

typedef unsigned char* byte_pointer;

int is_little_endian() {
    int val = 1;
    byte_pointer p = (byte_pointer) &val;
    if (p[0] == 0x01) return 1;
    return 0;
}

int main(int argc, char* argv[]) {
    printf("%d", is_little_endian());
    return is_little_endian();
}
