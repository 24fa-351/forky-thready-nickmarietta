#include <stdio.h>
#include <stdlib.h>

#include "forky.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <numOfThings> <pattern>\n", argv[0]);
        return 1;
    }

    int numOfThings = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if (numOfThings <= 0 || numOfThings > 256 || pattern < 1 || pattern > 2) {
        printf("Invalid arguments\n");
        return 1;
    }
    run_patterns(numOfThings, pattern);

    return 0;
}
