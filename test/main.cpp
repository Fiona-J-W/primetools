#include "calculate_primes.hpp"

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( BasicPrimes )

using primelist=std::vector<std::uintmax_t>;

bool check_calculate_primes_until(std::uintmax_t n, std::initializer_list<std::uintmax_t> expected) {
	const auto actual = primes::calculate_primes_until(n);
	return std::equal(actual.begin(), actual.end(), expected.begin(), expected.end());
}


BOOST_AUTO_TEST_CASE(test_tiny_calculate_primes_until) {
	BOOST_CHECK(check_calculate_primes_until(0, {}));
	BOOST_CHECK(check_calculate_primes_until(1, {}));
	BOOST_CHECK(check_calculate_primes_until(2, {2}));
	BOOST_CHECK(check_calculate_primes_until(3, {2, 3}));
	BOOST_CHECK(check_calculate_primes_until(4, {2, 3}));
	BOOST_CHECK(check_calculate_primes_until(5, {2, 3, 5}));
	BOOST_CHECK(check_calculate_primes_until(7, {2, 3, 5, 7}));
	BOOST_CHECK(check_calculate_primes_until(8, {2, 3, 5, 7}));
}

BOOST_AUTO_TEST_CASE(test_small_calculate_primes_until) {
	BOOST_CHECK(check_calculate_primes_until(11, {2,3,5,7,11}));
	BOOST_CHECK(check_calculate_primes_until(20, {2,3,5,7,11,13,17,19}));
	BOOST_CHECK(check_calculate_primes_until(30, {2,3,5,7,11,13,17,19,23,29}));
	BOOST_CHECK_EQUAL(primes::calculate_primes_until(10000u).back(), 9973);
	BOOST_CHECK_EQUAL(primes::calculate_primes_until(1u << 16u).back(), 65521);
}

BOOST_AUTO_TEST_CASE(test_large_calculate_primes_until) {
	BOOST_CHECK_EQUAL(primes::calculate_primes_until(65537u).back(), 65537);
	BOOST_CHECK_EQUAL(primes::calculate_primes_until(100000u).back(), 99991);
}

BOOST_AUTO_TEST_SUITE_END()
