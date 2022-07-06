#ifndef __PRIMALITY_UTILS_H
#define __PRIMALITY_UTILS_H

#include <stdbool.h>

unsigned long long base_generator(unsigned long long p);

unsigned long long modular_exp(unsigned long long base, unsigned long long exp, unsigned long long mod);

bool witness(unsigned long long a, unsigned long long p);

#endif