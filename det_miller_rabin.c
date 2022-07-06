#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "criterias.h"
#include "primality_utils.h"

//  deterministic implementation of Miller-Rabin primality test
bool det_miller_rabin(llu p)
{
    /*
    * Credits: https://rosettacode.org/wiki/Miller%E2%80%93Rabin_primality_test#Deterministic_up_to_341.2C550.2C071.2C728.2C321
    */
    if (p < 2)
        return true;
    
    //  p is even
    if (p != 2 && !(p & 1))
        return false;
    
    //  3 | p
    if(p % 3 == 0 && p != 3)
        return false;

    // p = 2 or p = 3
    if (p <= 3)
        return true;

    if (p < 1373653)
        return !witness(2, p) && !witness(3,p);
    
    if (p < 9080191)
        return !witness(31, p) && !witness(37,p);
    
    //  p < 4,294,967,295 (max value of a 32-bit unsigned integer) 
    return !witness(2, p) && !witness(7, p) && !witness(61, p);
}

bool is_probably_prime(llu p, int iterations)
{
    return det_miller_rabin(p);
}