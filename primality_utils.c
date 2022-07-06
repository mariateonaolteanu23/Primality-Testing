#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "primality_utils.h"

//  generate base in the interval [2, p-2]
unsigned long long base_generator(unsigned long long p)
{
    return rand() % (p - 2) + 2;
}

//  function computes base^exp % mod
unsigned long long modular_exp(unsigned long long base, unsigned long long exp, unsigned long long mod)
{
    unsigned long long result = 1;

    while (exp) {
        //  exponent is odd
        if (exp & 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

//  computes a^(p-1) mod p
/*
    returns true if a is a witness to the compositness of p
    false otherwise
*/
bool witness(unsigned long long a, unsigned long long p)
{
    unsigned long long x_0, x_i, u;

    //  p - 1 = 2^t * d
    //  where u is odd and t >= 1
    int t = 1;
    u = p / 2;

    while (u % 2 == 0) {
        u = u >> 1;
        t++;
    }

    //  compute a^u mod p
    x_0 = modular_exp(a, u, p);

    //  verify a^(2^i*u) = +1 / -1
    //  squaring x_0 t times
    for(int i = 0; i < t; ++i) {
        x_i = (x_0 * x_0) % p;

        //  found a nontrivial square root of 1 (mod p)
        if(x_i == 1 && x_0 != 1 && x_0 != p - 1)
            //  a is a witness to the compositness of p
            return true;
        
        x_0 = x_i;
    }

    //  doesn't pass the Fermat test
    //  a^(n - 1) mod p != 1
    if (x_i != 1)
        //  a is a witness to the compositness of p
        //  p is not prime
        return true;

    //  a is not a witness
    return false;
}
