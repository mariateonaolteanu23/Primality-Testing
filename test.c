#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "criterias.h"

//  entry point
int main(int argc, char** argv) 
{
    FILE *in, *out;
    llu prime_seq[MAX_ELEM];
    char request[MAX_INPUT_LINE] = {0};
    char* test_criteria;
    char* test_number;
    int primes;

    //  read input file
    in = fopen("test.in", "r");
    
    //  get test info
    fgets(request, MAX_INPUT_LINE, in);
    
    //  test criteria
    test_criteria = strtok(request, " ");

    //  test number
    test_number = strtok(NULL, "\n");
    int number = atoi(test_number);

    //  execution time test 
	if(!strncmp(test_criteria, "TIME", sizeof("TIME") - 1)) {
        test_for_time(in, 2 + argv[0], number, prime_seq, &primes);
    }
    
    //  accuracy test
    if(!strncmp(test_criteria, "ACCURACY", sizeof("ACCURACY") - 1)) {
        test_for_accuracy(in, 2 + argv[0], number, prime_seq, &primes);
    }

    //  print results in output file
    out = fopen("test.out", "w+");

    //  number of primes found
    fprintf(out, "%d\n", primes);

    //  the sequence of primes
    for(int i = 0; i < primes; ++i) {
        fprintf(out, "%llu ", prime_seq[i]);
    }

    fclose(out);
    fclose(in);
    (void)argc;
    
    return 0;
}