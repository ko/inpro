/**********************************************************************
 * main.c - zero compression
 *
 *  Goal: remove the zeroes from the list of ints.
 *
 *  Method: create a map of zero and non-zero values to prefix the 
 *          list of non-zero values. 
 *
 *  Example: 
 *
 *      input: 0 1 1 0 4 3 2 0
 *      intermediary:
 *          mask: 0x01101110h
 *          val: 11432d
 *      output: 118,11432
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define ARR_SIZE 17
#define MASK_LENGTH 8

void print_list(int size, int *compacts) {
    int i = 0;

    assert(compacts);

    printf("===\n");
    for (i = 0; i < size; i++) {
        printf("%d ", compacts[i]);
    }
    printf("\n");
    return;
}

int decode(int encode_size, int *encode, int **decode) {
    int i = 0, j = 0;
    int decode_count = 0;
    int value = 0;
    int *tmp = malloc(sizeof(int) * (MASK_LENGTH * encode_size / 2));
    
    for (i = 0; i < encode_size; i += 2 ) {

        for (j = 0; j < MASK_LENGTH; j++) {

            value = encode[i+1] % 10;
            encode[i+1] /= 10;

            tmp[decode_count] = value;

            decode_count++; 
        }
    }

    *decode = tmp;

    return decode_count;
}

int compress(int input_size, int *input, int **output) {
    int i, j;
    int mask = 0;
    int compact = 0;
    int *compacts = malloc(sizeof(int) * input_size + (input_size / MASK_LENGTH) + 1);
    int compacts_count = 0;

    for (i = 0; i < input_size; i += MASK_LENGTH) {
        mask = 0;
        compact = 0;

        for (j = 0; j < MASK_LENGTH; j++) {
            if ((i + j) >= input_size) {
                // oob. treat like zero
                mask |= 0 << j;
            } else {
                input[i+j] == 0 ? (mask |= 0 << j) : (mask |= 1 << j);

                // only works for single digits
                compact += (input[i+j] * (int)pow(10,j));
            }
        }

        compacts[compacts_count] = mask;
        compacts[compacts_count+1] = compact;
        compacts_count += 2; 
    }

    *output = compacts;

    return compacts_count;
}

int main(void) {
    int input[ARR_SIZE] = {0,1,1,0,
                     4,3,2,0,
                     0,0,1,1,
                     4,4,6,0,1};
    int output_size = 0, decode_size = 0;
    int *output = NULL, *decoded = NULL;

    output_size = compress(ARR_SIZE, input, &output);
    print_list(output_size, output);

    decode_size = decode(output_size, output, &decoded);
    print_list(decode_size, decoded);

    return 0;
}
