#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "criterias.h"

//  100% accurate primality test using trial division
bool is_prime(llu p)
{
    if (p < 2)
        return false;
    
    //  p is even
    if (p != 2 && !(p & 1))
        return false;

    //  3 | p
    if(p % 3 == 0 && p != 3)
        return false;

    //  5 | p
    if(p % 5 == 0 && p != 5)
        return false;

    //  7 | p
    if(p % 7 == 0 && p != 7)
        return false;

    //  p = 2 | p = 3 | p = 5 | p = 7
    if (p <= 7)
        return true;

    for (llu i = 11; i <= sqrt(p); i += 2) {
        if (p % i == 0) {
            //  number p is COMPOSITE
            return false;
        }
    }

    //  number p is PRIME
    return true;
}

/* This algorithm is not efficient for big numbers*/

/* We are only using the algorithm above to check the accuracy
 of Fermat and Miller-Rabin tests on 32-bits numbers*/

