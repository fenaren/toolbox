#include <cstdint>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(misc_test)

    TEST(Byteswap_InPlace)
    TEST(Byteswap_InPlaceTemplate)
    TEST(Byteswap_OutOfPlace)
    TEST(Endian_OperatorNot)
    TEST(SmallestMultipleOfXGreaterOrEqualToY)

TEST_CASES_END(misc_test)

const unsigned int SIZE = 8;

void initializeSquareMatrix(std::uint8_t (&m)[SIZE][SIZE]);
void initializeSquareMatrixSwapped(std::uint8_t (&m)[SIZE][SIZE]);
