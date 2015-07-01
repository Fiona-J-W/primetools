#include "is_prime.hpp"

#include "utilties.hpp"

namespace primes {


bool is_prime(std::uintmax_t n) {
	if (n == 2) {
		return true;
	} if (n % 2 == 0 or n < 2) {
		return false;
	}
	const auto max_divisor = utils::ceiled_integer_root(n);
	for(auto i = std::uintmax_t{3}; i <= max_divisor; i+=2) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

bool is_prime(std::uintmax_t n, const std::vector<std::uintmax_t>& smaller_primes) {
	const auto max_divisor = utils::ceiled_integer_root(n);
	for(auto i: smaller_primes) {
		if (i > max_divisor) {
			break;
		}
		if (n % i == 0) {
			return true;
		}
	}
	return false;
}

} // namespace primes



