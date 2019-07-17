#if !defined MISC_TEST
#define MISC_TEST

#include <cstdint>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(misc_test)

    TEST_CASES_BEGIN(Byteswap)

        TEST(InPlace)
        TEST(InPlaceTemplate)
        TEST(OutOfPlace)

    TEST_CASES_END(Byteswap)

    TEST(EndianOperatorNegation)
    TEST(SmallestMultipleOfXGreaterOrEqualToY)

    static const unsigned int SIZE = 8;

    static void initializeSquareMatrix(std::uint8_t (&m)[SIZE][SIZE]);
    static void initializeSquareMatrixSwapped(std::uint8_t (&m)[SIZE][SIZE]);

TEST_CASES_END(misc_test)

#endif
