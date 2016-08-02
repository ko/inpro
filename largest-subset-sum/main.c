#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Write a function that, given a list of integers (both positive and 
 * negative) returns the sum of the contiguous subsequence with 
 * maximum sum. Thus, given the sequence 
 *
 *  (1, 2, -4, 1, 3, -2, 3, -1) 
 *
 * it should return 5.
 */
int main(void) 
{
#define SIZEOF_INPUT 8
#define OUTPUT_START 0
#define OUTPUT_STOP 1
#define OUTPUT_SUM 2

    // int input[SIZEOF_INPUT] = { 1, 2, -4, 1, 3, -2, 3, -1 };
    // int input[SIZEOF_INPUT] = { 1, 2, -1, -2 };
    int input[SIZEOF_INPUT] = { 1, 2, -1, 1, 1 };
    int i, j, k, kSum;
    int out[3] = { 0 };

    for (i = 0; i < SIZEOF_INPUT; i++) {
        for (j = i; j < SIZEOF_INPUT; j++) {
            kSum = 0;
            for (k = i; k <= j; k++) {
                kSum += input[k];
            }

            if (kSum > out[OUTPUT_SUM]) {
                out[OUTPUT_START] = i;
                out[OUTPUT_STOP] = j;
                out[OUTPUT_SUM] = kSum;
            }
        }
    }

    printf("%s: sum of input[ %d ] to input [ %d ] = %d\n", __FUNCTION__, out[OUTPUT_START], out[OUTPUT_STOP], out[OUTPUT_SUM]);
}
