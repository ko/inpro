#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int stringSum(char * s) {

    int i;

    for (i = 0; i < strlen(s); i++) {

        i += s[i];
    }

    return i;
}

int isAnagram(char * s1, char * s2) {

    if (strlen(s1) == strlen(s2)) {

        if (stringSum(s1) == stringSum(s2)) {

            printf("'%s' and '%s' are anagrams\n", s1, s2);
            return 0;
        }
    }
    
    printf("'%s' and '%s' are not anagrams\n", s1, s2);
    return 1;
}

int main(void) {

    char * s1 = "hello";
    char * s2 = "holle";
    char * s3 = "holl";

    isAnagram(s1, s2);
    isAnagram(s2, s3);
}