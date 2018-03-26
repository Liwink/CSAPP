#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "unistd.h"
#include "cachelab.h"

void getoptions(int argc, char *argv[], int *s, int *E, int *b, char **t) {
    int opt;
    while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (opt) {
            case 's':
                *s = *optarg - 48;
                break;
            case 'E':
                *E = *optarg - 48;
                break;
            case 'b':
                *b = *optarg - 48;
                break;
            case 't':
                *t = optarg;
        }
    }
}

typedef struct POSITION {
    char type;
    int set;
    int tag;
    int addr;
} Position;

void readLine(Position *pos, char *line, int bVal, int sVal) {
    char addr[10];
    sscanf(line, "%s %[^,]", &pos->type, addr);
    printf("type: %s; addr: %s\n", &pos->type, addr);
    pos->addr = (int) strtol(addr, NULL, 16);
    int tmp = pos->addr / pow(2, bVal);
    pos->set = tmp % (int) pow(2, sVal);
    pos->tag = tmp / (int) pow(2, sVal);
}

int main(int argc, char *argv[])
{
    int sVal, EVal, bVal;
    char *tVal;

    FILE *fp;
    char *line = NULL;
    size_t len = 100;

    size_t cache_size;

    getoptions(argc, argv, &sVal, &EVal, &bVal, &tVal);

    // printf("s: %d\n", sVal);
    // printf("E: %d\n", EVal);
    // printf("b: %d\n", bVal);
    // printf("t: %s\n", tVal);

    cache_size = EVal * pow(2, sVal);
    printf("cache size: %zu\n", cache_size);
    int *cache = (int *) malloc(cache_size);
    cache[0] = 1;

    char *s_line = "L 4001ac,1";
    Position pos;
    readLine(&pos, s_line, bVal, sVal);
    printf("addr: %x\n", pos.addr);
    printf("set : %x\n", pos.set);
    printf("tag : %x\n", pos.tag);
    printf("type: %c\n", pos.type);

    // char type[10], addr[10];
    // char *s_line = "L 4001ac,1";
    // sscanf(s_line, "%s %[^,]", type, addr);
    // printf("type: %s; addr: %s\n", type, addr);
    // int num = (int) strtol(addr, NULL, 16);
    // int num1 = num / pow(2, bVal);
    // int num2 = num1 % (int) pow(2, sVal);
    // printf("num: %d; %x\n", num, num);
    // printf("   : %d; %x\n", num1, num1);
    // printf("   : %d; %x\n", num2, num2);
    // printf("   : %x\n", num % pow(2, sVal));

    fp = fopen(tVal, "r");
    while (getline(&line, &len, fp) != -1)
        printf("%s", line);

    printSummary(0, 0, 0);
    return 0;
}
