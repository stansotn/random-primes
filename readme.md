## Random Primes
Generate random primes of specified length in bits.

Currently does not work more on the issue [here](https://crypto.stackexchange.com/questions/89047/gmp-stuck-generating-same-random-integers).

Builds with
```shell
gcc main.cpp -O2 -Wall -std=c++14 -lstdc++ -lgmp -lgmpxx
```