#include "catch2/catch_all.hpp"
#include "solution.h"

TEST_CASE("isDigit() correctly recognizes digits")
{
	for(char c = '0'; c <= '9'; ++c)
		CHECK(isDigit(c));
}

TEST_CASE("isDigit() returns false for non-digits")
{
	for(int c = 0; c < '0'; ++c)
		CHECK_FALSE(isDigit(c));

	for(int c = '9'+1; c <= 127; ++c)
		CHECK_FALSE(isDigit(c));
}

TEST_CASE("isOperation() returns true for all operations")
{
	CHECK(isOperation('+'));
	CHECK(isOperation('-'));
	CHECK(isOperation('*'));
	CHECK(isOperation('/'));
	CHECK(isOperation('^'));
}

TEST_CASE("toDouble() correctly converts digits to their numeric values")
{
	int expected = 0;
	
	for(char c = '0'; c <= '9'; ++c)
		REQUIRE(expected++ == toDouble(c));
}

TEST_CASE("toDouble() throws when passed a non-digit character")
{
	REQUIRE_THROWS_AS(toDouble('x'), std::invalid_argument);
}

/// Check if two double values are equal with precision up to a specified delta
inline bool areSame(double a, double b, double delta = 0.0001)
{
	return std::abs(a - b) < delta;
}

/// Uses the CHECK macro to test whether two double values are the same with a specified precision
inline void checkSame(double a, double b, double delta = 0.0001)
{
	CHECK(areSame(a, b, delta));
}

TEST_CASE("perform('+', 1.5, 2.5) returns 4.0")
{
	checkSame(4.0, perform('+', 1.5, 2.5));
}

TEST_CASE("perform('-', 1.5, 2.5) returns -1.0")
{
	checkSame(-1.0, perform('-', 1.5, 2.5));
}	

TEST_CASE("perform('*', 1.5, 2.5) returns 3.75") {
	checkSame(3.75, perform('*', 1.5, 2.5));
}

TEST_CASE("perform('/', 1.5, 2.5) returns 0.6")
{
	checkSame(0.6, perform('/', 1.5, 2.5));
}

TEST_CASE("perform('^', 1.5, 2.5) returns 2.755675961") {
	checkSame(2.7556765961, perform('^', 1.5, 2.5));
}

TEST_CASE("perform() throws when dividing by zero")
{
	REQUIRE_THROWS_AS(perform('/', 5.0, 0.0), std::invalid_argument);
}

TEST_CASE("perform() throws when passed an invalid operation")
{
	REQUIRE_THROWS_AS(perform('x', 5.0, 5.0), std::invalid_argument);
}

TEST_CASE("evaluateRpn(nullptr) throws")
{
	REQUIRE_THROWS_AS(evaluateRpn(nullptr), std::invalid_argument);
}

TEST_CASE("evaluateRpn(\"\") returns 0")
{
	checkSame(0, evaluateRpn(""));
}

TEST_CASE("evaluateRpn() throws for an expression with invalid characters")
{
	REQUIRE_THROWS_AS(evaluateRpn("a5+"), std::invalid_argument);
	REQUIRE_THROWS_AS(evaluateRpn("5a5++"), std::invalid_argument);
}

TEST_CASE("evaluateRpn() respects argument order")
{
	SECTION("84/2/") {
		checkSame(1, evaluateRpn("84/2/"));    // 8/4/2
	}
	SECTION("84-2-") {
		checkSame(2, evaluateRpn("84-2-"));    // 8-4-2
	}
	SECTION("43^2^") {
		checkSame(4096, evaluateRpn("43^2^")); // 4^3^2
	}
	SECTION("842//") {
		checkSame(4, evaluateRpn("842//"));    // 8/4/2
	}
	SECTION("842--") {
		checkSame(6, evaluateRpn("842--"));    // 8-4-2
	}
	SECTION("432^^") {
		checkSame(262144, evaluateRpn("432^^")); // 4^3^2
	}	
}

TEST_CASE("evaluateRpn() correctly evaluates expressions")
{
	SECTION("23^2*2+5-") {
		checkSame(13, evaluateRpn("23^2*2+5-")); // 2^3*2+2-5
	}
	SECTION("5") {
		checkSame(5, evaluateRpn("5")); // 5
	}
	SECTION("32/") {
		checkSame(1.5, evaluateRpn("32/")); // 3/2
	}
	SECTION("23*4+") {
		checkSame(10, evaluateRpn("23*4+")); // 2*3+4
	}
	SECTION("234*+") {
		checkSame(14, evaluateRpn("234*+")); // 2+3*4
	}
	SECTION("3722^*-") {
		checkSame(-25, evaluateRpn("3722^*-")); // 3-7*2^2
	}
	SECTION("23+4+56*+7+8+") {
		checkSame(54, evaluateRpn("23+4+56*+7+8+")); // 2+3+4+5*6+7+8
	}
}

TEST_CASE("evaluateRpn() correctly returns an exception for invalid expressions")
{
	SECTION("23++"){
		REQUIRE_THROWS_AS(evaluateRpn("23++"), std::invalid_argument);
	}
	SECTION("23+4+*") {
		REQUIRE_THROWS_AS(evaluateRpn("23+4+*"), std::invalid_argument);
	}
	SECTION("23+4") {
		REQUIRE_THROWS_AS(evaluateRpn("23+4"), std::invalid_argument);
	}
}
