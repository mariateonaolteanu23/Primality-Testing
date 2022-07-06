#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "criterias.h"

//  get execution time for each test
void test_for_time(FILE* in, char* test_type, int test_number, llu prime_seq[MAX_ELEM], int* primes)
{
    FILE* file;
    int n, iterations;
    int prob_primes = 0;
    llu p;

    //  read number of trials 
    fscanf(in, "%d", &iterations);
    //  read sequence size
    fscanf(in, "%d", &n);

    //  start execution time
    clock_t start = clock();

    //  travers the sequence
    for(int i = 0; i < n; ++i) {
        //  read number p from file
        fscanf(in,"%llu", &p);
    
        //  number p is probably prime
        if (is_probably_prime(p, iterations)) {
            //  add to prime sequence
            prime_seq[prob_primes] = p;
            prob_primes++;
        }
    }

    //  get execution time
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

    //  print execution length in ms  
    file = fopen("./exec_time.out", "a");   
    fprintf(file, "Execution time for %s %d is %f ms.\n", test_type, test_number, elapsed);
    fclose(file);

    //  number of primes found in the given sequence
    *primes = prob_primes;
}

//  get data about accuracy
void test_for_accuracy(FILE* in, char* test_type, int test_number, llu prime_seq[MAX_ELEM], int* primes)
{
    FILE *tmp_file;
    int prob_primes = 0;
    int sure_primes = 0;
    int n, iterations;
    llu p;

    //  read number of trials 
    fscanf(in, "%d", &iterations);
    //  read sequence size
    fscanf(in, "%d", &n);
    
    //  create temporary file in case of test failure
    char file_name[MAX_FILE_NAME] = {0};
    sprintf(file_name, "./tmp/test[%d].out", (OFFSET + test_number));
    tmp_file = fopen(file_name, "a");

    //  fermat test using 1 trial base 
    if (!strncmp(test_type, "fermat_test", strlen("fermat_test") - 1))
        iterations = 1;
    
    //  print data regarding said failed test
    fprintf(tmp_file, "Primality %s using %d iterations failed for the following numbers:\n\n", test_type, iterations);

    //  travers the sequence 
    for(int i = 0; i < n; ++i) {
        //  read number p from file
        fscanf(in,"%llu", &p);
    
        //  number p is probably prime
        if (is_probably_prime(p, iterations)) {
            //  add to prime sequence
            prime_seq[prob_primes] = p;
            prob_primes++;

            //  number p is actually composite
            if (!is_prime(p)) {
                //  print number that returned false-positive result 
                fprintf(tmp_file, "%lld -> random bases selected:", p);

                //  print bases we tested for p
                for (int i = 0; i < iterations; ++i)
                fprintf(tmp_file, " %lld", bases[i]);
                fprintf(tmp_file, "\n\n");

            } else {
                //  number p is 100% prime
                sure_primes++;
            }
        }
    }

    //  number of primes found in the given sequence
    *primes = prob_primes;

    //  all the numbers declared probably prime are prime
    if (sure_primes == prob_primes) {
        //  test passed
        remove(file_name);
        return;
    }

    //  print error rate
    fprintf(tmp_file,"Out of %d numbers, %d returned a false-positive result.\n", n, prob_primes - sure_primes);
    fprintf(tmp_file, "Error rate of %.4f%%.\n", ((double)(prob_primes - sure_primes) / n)*100);
    fclose(tmp_file);
}
