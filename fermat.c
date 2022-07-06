#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "criterias.h"
#include "primality_utils.h"

//  selection of bases we can test for
int some_bases[10] = {2, 3, 4, 5, 7, 11, 13, 17, 31, 47};

//  Fermat test for only 1 trial base
bool pseudoprime(llu p) {

    if(p == 2)
        return 1;

   if (p < 2)
        return 0;
    
    //  p is even
    if (p != 2 && !(p & 1))
        return 0;

    //  Pick any base: {2, 3, 4, 5,...}
    llu a = 2;

    //  Base is greater than the number we test for
    //  A random base will be picked from some_bases
    if (a > p) {
        time_t t;
        srand((unsigned)time(&t));
    
        do 
            a = some_bases[rand() % 10];
        while (a >= p);
    }

    bases[0] = a;

    //  number p is COMPOSITE 
    if (modular_exp(a, p - 1, p) != 1) {
        return false;
    }

    //  number p is PSEUDOPRIME
    return true;
}

bool is_probably_prime(llu p, int iterations)
{
    iterations = 1;
    return pseudoprime(p);
}