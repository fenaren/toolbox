#if !defined DATA_PACKET_TEST
#define DATA_PACKET_TEST

#include <cstdint>

#include "DataPacket_test1.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(DataPacket_test)

    TEST(ReadRaw)
    TEST(ReadRawConstBuffer)
    TEST(WriteRaw)
    TEST(WriteRawConst)

    TEST_CASES_BEGIN(GetLengthBits)

        TEST(Align1Byte)
        TEST(Align2Byte)
        TEST(Align3Byte)
        TEST(Align4Byte)

    TEST_CASES_END(GetLengthBits)

    template <class T> static unsigned int pullField(T&            dptest_var,
                                                     std::uint8_t* raw_dptest,
                                                     unsigned int  offset);

    template <class T> static unsigned int pushField(std::uint8_t* raw_dptest,
                                                     T&            dptest_var,
                                                     unsigned int  offset);

TEST_CASES_END(DataPacket_test)

#endif
