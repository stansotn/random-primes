#include <iostream>

#include <gmp.h>


int main(int argc, const char **argv){

    // Max allowed input
    const auto max_bits = 8192; 
    // A composite number will be identified as a prime 
    // with an asymptotic probability of less than 4^(-reps).
    const auto resp = 30;

    if(argc != 2){

        std::cout<<"Invalid argument."<<std::endl;
        return 0;
    }
    
    // Limit to 8192 bits..
    auto n_bits = std::stoul(argv[1]);
    if(n_bits > max_bits){

        std::cout<<"Argument out of range."<<std::endl;
        return 0;
    }

    // Initialize mpz_max_allowed_int=2^n_bits - 1
    mpz_t mpz_max_allowed_int;
    mpz_init(mpz_max_allowed_int);
    mpz_ui_pow_ui(mpz_max_allowed_int, 2, n_bits);
    mpz_sub_ui(mpz_max_allowed_int, mpz_max_allowed_int, 1);

    // Initialize mpz_min_allowed_int=2^(n_bits - 1)
    mpz_t mpz_min_allowed_int;
    mpz_init(mpz_min_allowed_int);
    mpz_ui_pow_ui(mpz_min_allowed_int, 2, n_bits-1);
    mpz_add_ui(mpz_min_allowed_int, mpz_min_allowed_int, 1); // add 1 to make odd.

    // Random odd int of n bits.
    mpz_t mpz_int;
    gmp_randstate_t state;
    mpz_init(mpz_int);
    gmp_randinit_default(state);
    mpz_rrandomb(mpz_int, state, (mp_bitcnt_t)n_bits);

    std::cout<<"Random int generated:"<<std::endl;
    std::cout<<mpz_get_str(nullptr, 10, mpz_int)<<std::endl;
    std::cout<<std::endl;

    // Make sure mpz_int is odd.
    if(mpz_even_p(mpz_int)){

        mpz_add_ui(mpz_int, mpz_int, 1);
    }

    // We can't blindly use next_prime function because depending on the
    // random number generated, next_prime might not fit in n bits.
    while(true){

        if(mpz_probab_prime_p(mpz_int, resp)){

            std::cout<<"Random prime generated:"<<std::endl;
            std::cout<<mpz_get_str(nullptr, 10, mpz_int)<<std::endl;

            return 0;
        }

        mpz_add_ui(mpz_int, mpz_int, 2);

        // If mpz_int reached the max amount length in n_bits
        if(mpz_cmp(mpz_int, mpz_max_allowed_int) > 0){

            mpz_set(mpz_int, mpz_min_allowed_int);
        }
    }

    return 0;
}