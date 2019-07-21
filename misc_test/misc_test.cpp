#include <cstdint>
#include <cstring>
#include <iostream>

#include "misc_test.hpp"

#include "TestMacros.hpp"
#include "misc.hpp"

TEST_PROGRAM_MAIN(misc_test)

//==============================================================================
void misc_test::addTestCases()
{
    ADD_TEST_CASE(Byteswap);
    ADD_TEST_CASE(EndianOperatorNegation);
    ADD_TEST_CASE(SmallestMultipleOfXGreaterOrEqualToY);
}

//==============================================================================
void misc_test::Byteswap::addTestCases()
{
    ADD_TEST_CASE(InPlace);
    ADD_TEST_CASE(InPlaceTemplate);
    ADD_TEST_CASE(OutOfPlace);
}

//==============================================================================
Test::Result misc_test::Byteswap::InPlace::body()
{
    // Use two test matrices, one with the rows initialized in opposite order
    std::uint8_t workspace1[SIZE][SIZE];
    std::uint8_t workspace2[SIZE][SIZE];
    initializeSquareMatrix(workspace1);
    initializeSquareMatrixSwapped(workspace2);

    for (unsigned int i = 0; i < SIZE; ++i)
    {
        misc::byteswap(workspace1[i], i + 1);
        MUST_BE_TRUE(memcmp(workspace1[i], workspace2[i], i + 1) == 0);
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result misc_test::Byteswap::InPlaceTemplate::body()
{
    std::uint32_t someuint = 3091572734;
    misc::byteswap(someuint);

    // Used MacOS built-in calculator app to calcluate this
    MUST_BE_TRUE(someuint == 4272375224);

    return Test::PASSED;
}

//==============================================================================
Test::Result misc_test::Byteswap::OutOfPlace::body()
{
    // Use two test matrices, one with the rows initialized in opposite order
    std::uint8_t workspace1[SIZE][SIZE];
    std::uint8_t workspace2[SIZE][SIZE];
    std::uint8_t workspace3[SIZE][SIZE];
    initializeSquareMatrix(workspace1);
    initializeSquareMatrix(workspace2);
    initializeSquareMatrixSwapped(workspace3);

    for (unsigned int i = 0; i < SIZE; ++i)
    {
        misc::byteswap(workspace2[i], workspace1[i], i + 1);
        MUST_BE_TRUE(memcmp(workspace2[i], workspace3[i], i + 1) == 0);
    }

    return Test::PASSED;
}

//==============================================================================
Test::Result misc_test::EndianOperatorNegation::body()
{
    // Test operator! on values of the ByteOrder enumeration
    MUST_BE_TRUE(misc::ENDIAN_LITTLE == !misc::ENDIAN_BIG);
    MUST_BE_TRUE(misc::ENDIAN_BIG    == !misc::ENDIAN_LITTLE);

    return Test::PASSED;
}

//==============================================================================
Test::Result misc_test::SmallestMultipleOfXGreaterOrEqualToY::body()
{
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(1,  2)  == 2);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(2,  2)  == 2);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(2,  5)  == 6);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(2,  6)  == 6);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(14, 0)  == 0);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(14, 2)  == 14);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(14, 20) == 28);

    return Test::PASSED;
}

//==============================================================================
void misc_test::initializeSquareMatrix(std::uint8_t (&m)[SIZE][SIZE])
{
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        for (unsigned int j = 0; j < i + 1; ++j)
        {
            m[i][j] = j;
        }
    }
}

//==============================================================================
void misc_test::initializeSquareMatrixSwapped(std::uint8_t (&m)[SIZE][SIZE])
{
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        for (unsigned int j = i; j > 0; --j)
        {
            m[i][j] = i - j;
        }

        m[i][0] = i;
    }
}
