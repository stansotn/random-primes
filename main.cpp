#include <iostream>

#include "randomprime.h"

int main(int argc, const char **argv){

    // Max allowed input
    const auto max_bits = 8192; 
    const auto resp = 30;

    if(argc != 2){

        std::cerr<<"Invalid argument."<<std::endl;
        return 0;
    }
    
    // Limit to 8192 bits..
    const auto n_bits = std::stoul(argv[1]);
    if(n_bits > max_bits){

        std::cerr<<"Argument out of range."<<std::endl;
        return 0;
    }

    mpz_t mpz_rand_prime;
    mpz_init(mpz_rand_prime);

    // This will print the random prime to stdout.
    randomprime(mpz_rand_prime, n_bits, resp);

    return 0;
}