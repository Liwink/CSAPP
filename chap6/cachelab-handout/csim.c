#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "cachelab.h"

int main(int argc, char *argv[])
{
    int opt;
    int sVal, EVal, bVal;
    char *tVal;
    FILE *fp;
    char *line = NULL;
    size_t len = 100;

    while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (opt) {
            case 's':
                sVal = *optarg - 48;
                break;
            case 'E':
                EVal = *optarg - 48;
                break;
            case 'b':
                bVal = *optarg - 48;
                break;
            case 't':
                tVal = optarg;
        }
    }
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
