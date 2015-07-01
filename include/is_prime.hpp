#ifndef PRIMES_IS_PRIME_HPP
#define PRIMES_IS_PRIME_HPP

#include <cstdint>
#include <vector>


namespace primes {

bool is_prime(std::uintmax_t n);
bool is_prime(std::uintmax_t n, const std::vector<std::uintmax_t>& smaller_primes);


} // namespace primes


#endif
