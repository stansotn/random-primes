# Random Primes
Generate random primes p of length n bits such that.

2^(n-1) <= p <= 2^n - 1

## Build
1. Set the desired maximum length of the generated randoms. Defaults to 8196
```cpp
// Random int of n bits.
const auto n_bits = 8192;
```

```shell
gcc main.cpp -O2 -Wall -std=c++14 -lstdc++ -lgmp -lgmpxx
```

Relies on `/dev/urandom` to get a random seed of size `unsigned long int`.

## Run
Simply invoke executable with a desired bit length as an argument.
```shell
randomprime 8192
```

## Profile

`profile.py` allows benchmarking random prime generation. For each lenght of `n_bits` in range [`n_start`, `n_stop`] the script will generate `n_samples` of random primes timing the generation of each sample. Mean sample generation time and standard deviation will then be saved into a csv file.

Unix tool `time` is used as a profiler. For runtimes less than 10 milliseconds `time` returns 0. Therefore it is not recommended to set the `n_start` bits to anything less than 1024 or you might see zeros in the resulting csv (depends on how fast is your computer).