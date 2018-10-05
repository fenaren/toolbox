#include <cstring>

#include "misc_test_case1.hpp"

#include "TestMacros.hpp"
#include "misc.hpp"

//==============================================================================
misc_test_case1::misc_test_case1()
{
}

//==============================================================================
misc_test_case1::~misc_test_case1()
{
}

//==============================================================================
Test::Result misc_test_case1::run()
{
    unsigned char a1_before[] = {'a'};
    unsigned char a2_before[] = {'a', 'b'};
    unsigned char a3_before[] = {'a', 'b', 'c'};
    unsigned char a4_before[] = {'a', 'b', 'c', 'd'};
    unsigned char a5_before[] = {'a', 'b', 'c', 'd', 'e'};
    unsigned char a6_before[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    unsigned char a7_before[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    unsigned char a8_before[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    unsigned char a1_after[] = {'a'};
    unsigned char a2_after[] = {'b', 'a'};
    unsigned char a3_after[] = {'c', 'b', 'a'};
    unsigned char a4_after[] = {'d', 'c', 'b', 'a'};
    unsigned char a5_after[] = {'e', 'd', 'c', 'b', 'a'};
    unsigned char a6_after[] = {'f', 'e', 'd', 'c', 'b', 'a'};
    unsigned char a7_after[] = {'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    unsigned char a8_after[] = {'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};

    misc::byteswap(a1_before, 1);
    misc::byteswap(a2_before, 2);
    misc::byteswap(a3_before, 3);
    misc::byteswap(a4_before, 4);
    misc::byteswap(a5_before, 5);
    misc::byteswap(a6_before, 6);
    misc::byteswap(a7_before, 7);
    misc::byteswap(a8_before, 8);

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
