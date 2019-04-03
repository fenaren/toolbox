#include <cstdint>
#include <iostream>

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_CASES_PROGRAM_BEGIN(misc_test)
TEST(Byteswap_InPlace)
TEST(Byteswap_OutOfPlace)
TEST_CASES_PROGRAM_END(misc_test)

const unsigned int SIZE = 8;

void initializeSquareMatrix(std::uint8_t (&m)[SIZE][SIZE]);
void initializeSquareMatrixSwapped(std::uint8_t (&m)[SIZE][SIZE]);

//==============================================================================
void misc_test::addTestCases()
{
    addTestCase(new Byteswap_InPlace());
//    addTestCase(new Byteswap_OutOfPlace());
}

//==============================================================================
Test::Result misc_test::Byteswap_InPlace::body()
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
/*
//==============================================================================
Test::Result misc_test::Byteswap_OutOfPlace::body()
{
    unsigned char a1_backwards[] = {0};
    unsigned char a2_backwards[] = {0, 0};
    unsigned char a3_backwards[] = {0, 0, 0};
    unsigned char a4_backwards[] = {0, 0, 0, 0};
    unsigned char a5_backwards[] = {0, 0, 0, 0, 0};
    unsigned char a6_backwards[] = {0, 0, 0, 0, 0, 0};
    unsigned char a7_backwards[] = {0, 0, 0, 0, 0, 0, 0};
    unsigned char a8_backwards[] = {0, 0, 0, 0, 0, 0, 0, 0};

    misc::byteswap(a1_backwards, a1, 1);
    misc::byteswap(a2_backwards, a2, 2);
    misc::byteswap(a3_backwards, a3, 3);
    misc::byteswap(a4_backwards, a4, 4);
    misc::byteswap(a5_backwards, a5, 5);
    misc::byteswap(a6_backwards, a6, 6);
    misc::byteswap(a7_backwards, a7, 7);
    misc::byteswap(a8_backwards, a8, 8);

    MUST_BE_TRUE(memcmp(a1_before, a1_after, 1) == 0);
    MUST_BE_TRUE(memcmp(a2_before, a2_after, 2) == 0);
    MUST_BE_TRUE(memcmp(a3_before, a3_after, 3) == 0);
    MUST_BE_TRUE(memcmp(a4_before, a4_after, 4) == 0);
    MUST_BE_TRUE(memcmp(a5_before, a5_after, 5) == 0);
    MUST_BE_TRUE(memcmp(a6_before, a6_after, 6) == 0);
    MUST_BE_TRUE(memcmp(a7_before, a7_after, 7) == 0);
    MUST_BE_TRUE(memcmp(a8_before, a8_after, 8) == 0);

    return Test::PASSED;
}
/*
    // Test operator! on values of the ByteOrder enumeration
    MUST_BE_TRUE(misc::ENDIAN_LITTLE == !misc::ENDIAN_BIG);
    MUST_BE_TRUE(misc::ENDIAN_BIG    == !misc::ENDIAN_LITTLE);

    // At this point we're satisfied with he performance of the other two
    // byteswap functions, so we should be okay to use those to test the
    // template byteswap function
    std::uint32_t a4_int;
    memcpy(&a4_int, a4_before, sizeof(std::uint32_t));
    misc::byteswap(a4_int);
    misc::byteswap(a4_after, 4);

    // a4_before and a4_after were the same before this test, and we should have
    // applied the same operation to both of them, so they should be the same
    // afterwards
    MUST_BE_TRUE(
        memcmp(a4_after, reinterpret_cast<unsigned char*>(&a4_int), 4) == 0);

    // A bunch of smallestMultiple tests
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(1,  2)  == 2);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(2,  2)  == 2);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(2,  5)  == 6);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(2,  6)  == 6);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(14, 0)  == 0);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(14, 2)  == 14);
    MUST_BE_TRUE(misc::smallestMultipleOfXGreaterOrEqualToY(14, 20) == 28);

    return Test::PASSED;
}
*/

//==============================================================================
void initializeSquareMatrix(std::uint8_t (&m)[SIZE][SIZE])
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
void initializeSquareMatrixSwapped(std::uint8_t (&m)[SIZE][SIZE])
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
