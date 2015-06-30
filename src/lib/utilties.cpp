#include "utilties.hpp"

#include <limits>
#include <iostream>

namespace primes {
namespace utils {

namespace {
constexpr std::uintmax_t square(std::uintmax_t n) { return n * n; }
}

constexpr static auto max_root =
        (std::numeric_limits<std::uintmax_t>::max() >> (sizeof(std::uintmax_t) * 8u / 2u));
constexpr static auto max_regular_square = square(max_root - 1u);

std::uintmax_t ceiled_integer_root(std::uintmax_t n) {
	if (n > max_regular_square) {
		return max_root + 1u;
	}
	auto low = std::uintmax_t{};
	auto high = std::uintmax_t{1} << std::uintmax_t{sizeof(std::uintmax_t) * 8u / 2u};
	while (high - low > 4u) {
		const auto avg = low + (high - low) / 2u;
		std::cout << "low = " << low << ", high = " << high << ", avg = " << avg << '\n';
		const auto square = avg * avg;
		if (square < n) {
			low = avg;
		} else {
			high = avg;
		}
	}
	while (low * low < n) {
		std::cout << "low = " << low << ", n = " << n << '\n';
		++low;
	}
	return low;
}
}
} // namespaces
