#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int primeTimes(char * s) {

    int i;
    int product = 1;
    int primes[26] = { 2,  3,  5,  7, 11, 
                      13, 17, 19, 23, 29, 
                      31, 37, 41, 43, 47, 
                      53, 57, 59, 61, 67, 
                      71, 73, 79, 83, 89, 
                      97 };

    for (i = 0; i < strlen(s); i++) {

        product = product * primes[s[i] - 'a']; 
    }


    return product;
}

int isAnagram(char * s1, char * s2) {

    if (primeTimes(s1) == primeTimes(s2)) {

        printf("'%s' and '%s' are anagrams\n", s1, s2);
        return 0;
    } else {

        printf("'%s' and '%s' are not anagrams\n", s1, s2);
        return 1;
    }
    
}

int main(void) {

    char * s1 = "hello";
    char * s2 = "holle";
    char * s3 = "holl";
    char * s4 = "ad";
    char * s5 = "bc";

    isAnagram(s1, s2);
    isAnagram(s2, s3);
    isAnagram(s4, s5);
}
