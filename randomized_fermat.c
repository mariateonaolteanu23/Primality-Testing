#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "criterias.h"
#include "primality_utils.h"

//  randomized Fermat primality test
//  we test the Fermat algorithm for multiple random bases
bool rand_fermat(llu p, int iterations) {

    if(p == 2)
        return 1;

    if (p < 2)
        return 0;
    
    //  p is even
    if (p != 2 && !(p & 1))
        return 0;
    
    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < iterations; ++i) {

        //  generate random base
        llu a = base_generator(p);
        bases[i] = a;

        //  number p is COMPOSITE
        if (modular_exp(a, p - 1, p) != 1) {
            return false;
        }
    }

    //  number p is probably PRIME
    return true;
}

bool is_probably_prime(llu p, int iterations)
{
    return rand_fermat(p, iterations);

}

