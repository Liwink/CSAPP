#define _GNU_SOURCE
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "unistd.h"
#include "cachelab.h"

void getoptions(int argc, char *argv[], int *S, int *E, int *B, char **t) {
    int opt;
    while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (opt) {
            case 's':
                *S = pow(2, *optarg - 48);
                break;
            case 'E':
                *E = *optarg - 48;
                break;
            case 'b':
                *B = pow(2, *optarg - 48);
                break;
            case 't':
                *t = optarg;
        }
    }
}

typedef struct POSITION {
    char type;
    int set;
    long tag;
    long addr;
} Position;

void readLine(Position *pos, char *line, int BVal, int SVal) {
    char addr[10];
    sscanf(line, "%s %[^,]", &pos->type, addr);
    pos->addr = strtol(addr, NULL, 16);
    long tmp = pos->addr / BVal;
    pos->set = tmp % (int) SVal;
    pos->tag = tmp / (int) SVal;
}

int main(int argc, char *argv[])
{
    int SVal, EVal, BVal;
    char *tVal;

    FILE *fp;
    char *line = NULL;
    size_t len = 100;

    size_t cache_size;

    getoptions(argc, argv, &SVal, &EVal, &BVal, &tVal);

    cache_size = EVal * SVal * 2;
    printf("cache size: %zu\n", cache_size);
    int *cache = (int *) malloc(cache_size * sizeof(int));
    int j;
    for (j = 0; j < cache_size; j++) {
        cache[j] = -1;
    }

    Position pos;
    int hit = 0, miss = 0, evict = 0;
    int start, i;
    int is_hit, is_evict;
    int small_count, small_index;
    int count = 0;
    fp = fopen(tVal, "r");
    while (getline(&line, &len, fp) != -1) {
        readLine(&pos, line, BVal, SVal);
        if (pos.type == 'I')
            continue;

        is_hit = 0;
        is_evict = 1;
        small_count = count;
        printf("addr: %lx; set: %x; tag: %lx; type: %c\n", pos.addr, pos.set, pos.tag, pos.type);
        start = pos.set * EVal * 2;
        for (i = 0; i < EVal; i++) {
            if (cache[start + i * 2] == pos.tag) {
                is_hit = 1;
                is_evict = 0;
                small_index = i;
                break;
            }
            else if (cache[start + i * 2 + 1] == -1) {
                is_evict = 0;
                small_index = i;
                break;
            }
            else if (cache[start + i * 2 + 1] <= small_count) {
                small_count = cache[start + i * 2 + 1];
                small_index = i;
            }
        }

        if (is_hit)
            hit++;
        else {
            miss++;
            cache[start + small_index * 2] = pos.tag;
            if (is_evict == 1)
                evict++;
        }
        cache[start + small_index * 2 + 1] = count;

        if (pos.type == 'M')
            hit++;
        printf("hit: %d; evict: %d\n", is_hit, is_evict);

        count++;
    }

    free(cache);
    cache = NULL;
    printSummary(hit, miss, evict);
    return 0;
}
