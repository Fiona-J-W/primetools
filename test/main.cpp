#include "calculate_primes.hpp"
#include "is_prime.hpp"
#include "utilties.hpp"

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

BOOST_AUTO_TEST_CASE(test_is_prime_no_precalc) {
	BOOST_CHECK(primes::is_prime(2));
	BOOST_CHECK(primes::is_prime(3));
	BOOST_CHECK(primes::is_prime(5));
	BOOST_CHECK(primes::is_prime(7));
	BOOST_CHECK(primes::is_prime(11));
	BOOST_CHECK(primes::is_prime(13));
	BOOST_CHECK(primes::is_prime(17));
	BOOST_CHECK(primes::is_prime(19));
	BOOST_CHECK(primes::is_prime(199));
	BOOST_CHECK(primes::is_prime(65521));
	BOOST_CHECK(primes::is_prime(99991));

	BOOST_CHECK(!primes::is_prime(0));
	BOOST_CHECK(!primes::is_prime(1));
	BOOST_CHECK(!primes::is_prime(4));
	BOOST_CHECK(!primes::is_prime(6));
	BOOST_CHECK(!primes::is_prime(9));
	BOOST_CHECK(!primes::is_prime(15));
	BOOST_CHECK(!primes::is_prime(25));
	BOOST_CHECK(!primes::is_prime(99993));
	BOOST_CHECK(!primes::is_prime(123456));
	BOOST_CHECK(!primes::is_prime(111111));
	BOOST_CHECK(!primes::is_prime(1234567890));
}

BOOST_AUTO_TEST_CASE(test_is_prime_precalc) {
	const auto primes = primes::calculate_primes_until(primes::utils::ceiled_integer_root(1234567890));
	BOOST_CHECK(primes::is_prime(2, primes));
	BOOST_CHECK(primes::is_prime(3, primes));
	BOOST_CHECK(primes::is_prime(5, primes));
	BOOST_CHECK(primes::is_prime(7, primes));
	BOOST_CHECK(primes::is_prime(11, primes));
	BOOST_CHECK(primes::is_prime(13, primes));
	BOOST_CHECK(primes::is_prime(17, primes));
	BOOST_CHECK(primes::is_prime(19, primes));
	BOOST_CHECK(primes::is_prime(199, primes));
	BOOST_CHECK(primes::is_prime(65521, primes));
	BOOST_CHECK(primes::is_prime(99991, primes));

	BOOST_CHECK(!primes::is_prime(0, primes));
	BOOST_CHECK(!primes::is_prime(1, primes));
	BOOST_CHECK(!primes::is_prime(4, primes));
	BOOST_CHECK(!primes::is_prime(6, primes));
	BOOST_CHECK(!primes::is_prime(9, primes));
	BOOST_CHECK(!primes::is_prime(15, primes));
	BOOST_CHECK(!primes::is_prime(25, primes));
	BOOST_CHECK(!primes::is_prime(99993, primes));
	BOOST_CHECK(!primes::is_prime(123456, primes));
	BOOST_CHECK(!primes::is_prime(111111, primes));
	BOOST_CHECK(!primes::is_prime(1234567890, primes));
}


BOOST_AUTO_TEST_CASE(test_ceiled_integer_root) {
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(8), 3);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(9), 3);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(10), 4);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(11), 4);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(16), 4);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(10000), 100);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(100000000), 10000);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(4611686009837453316u), 2147483646u);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(18446744056529682436u), 4294967294u);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(18446744056529682437u), 4294967296u);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(18446744073709551614u), 4294967296u);
	BOOST_CHECK_EQUAL(primes::utils::ceiled_integer_root(18446744073709551615u), 4294967296u);
}


BOOST_AUTO_TEST_SUITE_END()
