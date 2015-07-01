#include "calculate_primes.hpp"

#include <stdexcept>
#include <cassert>

#include "utilties.hpp"

namespace primes {

namespace {
std::vector<std::uintmax_t> calculate_tiny_primes_until(std::size_t n) {
	switch (n) {
	case 0:
	case 1:
		return {};
	case 2:
		return {2};
	case 3:
	case 4:
		return {2, 3};
	case 5:
	case 6:
		return {2, 3, 5};
	case 7:
	case 8:
	case 9:
	case 10:
		return {2, 3, 5, 7};
	default:
		throw std::invalid_argument{"n to large for calculate_tiny_primes_until()"};
	}
}
std::vector<std::uintmax_t> calculate_small_primes_until(std::size_t n) {
	auto candidates = std::vector<std::uint8_t>(n + 1u, 1);
	candidates[0] = 0;
	candidates[1] = 0;
	const auto max_candidat = utils::ceiled_integer_root(n);
	for (auto i = std::size_t{3}; i <= max_candidat; i += 2) {
		if (candidates[i] == 0) {
			continue;
		}
		for (auto j = i * i; j <= n; j += 2 * i) {
			candidates[j] = 0;
		}
	}
	auto primes = std::vector<std::size_t>{2};
	for (auto i = std::size_t{3}; i <= n; i += 2) {
		if (candidates[i]) {
			primes.push_back(i);
		}
	}
	return primes;
}

void calculate_large_primes_until(std::uintmax_t n, std::uintmax_t i, std::vector<std::uintmax_t>& primes) {
	while(i <= n) {
		auto is_prime = true;
		for(auto p: primes) {
			if(p*p > i) {
				break;
			}
			if (i%p == 0) {
				is_prime = false;
				break;
			}
		}
		if (is_prime) {
			primes.push_back(i);
		}
		i+=2;
	}
}

} // anonymous namespace

std::vector<std::uintmax_t> calculate_primes_until(std::uintmax_t n) {
	if (n < 11) {
		return calculate_tiny_primes_until(n);
	}
	const auto small_threshold = std::uintmax_t{1u} << 16u;
	auto found_primes = calculate_small_primes_until(std::min(n, small_threshold));
	if (n < small_threshold) {
		return found_primes;
	}
	calculate_large_primes_until(n, small_threshold+1u, found_primes);
	return found_primes;
}

} // namespace primes
