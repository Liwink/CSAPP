#include "stdio.h"
#include "stdlib.h"
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

int main(int argc, char *argv[])
{
    int sVal, EVal, bVal;
    char *tVal;

    FILE *fp;
    char *line = NULL;
    size_t len = 100;

    getoptions(argc, argv, &sVal, &EVal, &bVal, &tVal);

    printf("s: %d\n", sVal);
    printf("E: %d\n", EVal);
    printf("b: %d\n", bVal);
    printf("t: %s\n", tVal);

    fp = fopen(tVal, "r");
    while (getline(&line, &len, fp) != -1)
        printf("%s", line);

    printSummary(0, 0, 0);
    return 0;
}
