#ifndef TESTS_H
#define TESTS_H

#include <cstdio>

/// Standard test, outputs expr on failure
#define TEST(expr) ( \
	static_cast<bool>(expr) \
	? void(0) \
	: ( \
		++result, \
		std::printf("Test failed at %s:%i: %s\n", __FILE__, __LINE__, #expr), \
		void(0) \
	) \
)

/// Test with a custom failure message
#define TEST_MSG(expr, msg) ( \
	static_cast<bool>(expr) \
	? void(0) \
	: ( \
		++result, \
		std::printf("Test failed at %s:%i: %s\n", __FILE__, __LINE__, msg), \
		void(0) \
	) \
)

/// Comparison test: will output the expected and recieved values on failure. Values must be string-convertable.
#define COMPARE(expr, expected) ( \
	(expr == expected) \
	? void(0) \
	: ( \
		++result, \
		std::printf("Test failed at %s:%i: `%s` expected %s, recieved %s\n", __FILE__, __LINE__, #expr, std::to_string(expected).c_str(), std::to_string(expr).c_str()), \
		void(0) \
	) \
)

/// Compares a floating point within a margin.
#define COMPARE_WITHIN(expr, expected, margin) ( \
	(std::abs(expr - expected) < margin) \
	? void(0) \
	: ( \
		++result, \
		std::printf("Test failed at %s:%i: `%s` expected %g±%g, recieved %g\n", __FILE__, __LINE__, #expr, expected, margin, expr), \
		void(0) \
	) \
)

/// Run a test function
#define RUN_TEST(expr) do { result += expr; } while (0)

int testShapes();

#endif // TESTS_H
