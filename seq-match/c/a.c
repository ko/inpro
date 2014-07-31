#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PATTERN_SZ 5
#define TARGET_SZ 10
int main() {

    char pattern[PATTERN_SZ] = "bsd";
    char target[TARGET_SZ] = "lbisnudx";

    int i, j;

    int k;

    for (i = 0; i < strlen(pattern); i++) {
        for (j = 0; j < strlen(target); j++) {
            if (pattern[i] == target[j]) {
                k++;
                break;
            }
        }
    }

    if (k == strlen(pattern)) {
        return 1;
    } else {
        return 0;
    }
}
