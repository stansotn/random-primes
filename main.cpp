#include <iostream>
#include <fstream>

#include <gmp.h>


int main(int argc, const char **argv){

    // Max allowed input
    const auto max_bits = 8192; 
    // A composite number will be identified as a prime 
    // with an asymptotic probability of less than 4^(-reps).
    const auto resp = 30;

    if(argc != 2){

        std::cerr<<"Invalid argument."<<std::endl;
        return 0;
    }
    
    // Limit to 8192 bits..
    auto n_bits = std::stoul(argv[1]);
    if(n_bits > max_bits){

        std::cerr<<"Argument out of range."<<std::endl;
        return 0;
    }

    // Get random seed
    //Declare value to store seed into
    unsigned long int random_seed = 0;

    //Open stream
    std::ifstream urandom("/dev/urandom", std::ios::in|std::ios::binary); 

    if(not urandom){

        std::cerr << "Failed to open /dev/urandom" << std::endl;
        return 0;
    }
    //Read from urandom
    urandom.read(reinterpret_cast<char*>(&random_seed), sizeof(random_seed)); 

    // Check if stream is ok, read succeeded
    if(not urandom){
    
        std::cerr << "Failed to read from /dev/urandom" << std::endl;
        return 0;
    }
    // close stream
    urandom.close();

    // Random odd int of n bits.
    mpz_t mpz_int;
    gmp_randstate_t state;
    mpz_init(mpz_int);
    gmp_randinit_default(state);
    gmp_randseed_ui(state, random_seed);
    mpz_rrandomb(mpz_int, state, n_bits);

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

    // Make sure mpz_int is odd.
    if(mpz_even_p(mpz_int)){

        mpz_add_ui(mpz_int, mpz_int, 1);
    }

    // We can't blindly use gmp's next_prime function because depending on the
    // random number generated, next_prime might not fit in n bits.
    while(true){

        if(mpz_probab_prime_p(mpz_int, resp)){

            std::cout<<"Random prime generated:"<<std::endl;
            std::cout<<mpz_get_str(nullptr, 10, mpz_int)<<std::endl;

            return 0;
        }
        // mpz_int += 2
        mpz_add_ui(mpz_int, mpz_int, 2);

        // If mpz_int reached the max amount length in n_bits
        if(mpz_cmp(mpz_int, mpz_max_allowed_int) > 0){
            
            // Reset mpz_int to 2^(n_bits-1) + 1
            mpz_set(mpz_int, mpz_min_allowed_int);
        }
    }

    return 0;
}