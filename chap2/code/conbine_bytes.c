#include <stdio.h>

int main(int argc, char* argv[]) {
    int x = 0x89ABCDEF;
    int y = 0x76543210;

    int result = (y & 0xFFFFFF00) | (x & 0x000000FF);
    printf("%x", result);
}
