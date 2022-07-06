#ifndef __CRITERIAS_H
#define __CRITERIAS_H

#include <stdbool.h>

//  max elements of input sequence
#define MAX_ELEM 1000000

//  max input line for test info
#define MAX_INPUT_LINE 20

//  max trials tested for
#define MAX_ITER 64

#define MAX_FILE_NAME 50

#define OFFSET 30

typedef unsigned long long llu;
llu bases[MAX_ITER];

/*
    true for probably PRIME
    false for COMPOSITE
*/
bool is_probably_prime(llu p, int iterations);

/*
    true for PRIME
    false for COMPOSITE
*/
bool is_prime(llu p);

//  execution time test
void test_for_time(FILE* in, char* test_type, int test_number, llu prime_seq[MAX_ELEM], int* primes);

//  accuracy test
void test_for_accuracy(FILE* in, char* test_type, int test_number, llu prime_seq[MAX_ELEM], int* primes);

#endif
