#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "criterias.h"
#include "primality_utils.h"

// Miller-Rabin primality test
bool miller_rabin(llu p, int iterations)
{
    
    if (p == 2)
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

        //  number p is COMPOSITE with a as witness
        if (witness(a, p)) {
            return false;
        }
    }

    //  number p is probably PRIME
    return true;
}

bool is_probably_prime(llu p, int iterations)
{
    return miller_rabin(p, iterations);
}
