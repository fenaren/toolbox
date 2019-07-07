#if !defined DATA_PACKET_TEST
#define DATA_PACKET_TEST

#include "DataPacket_test1.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(DataPacket_test)

    TEST_CASES_BEGIN(ReadRaw)
    TEST_CASES_END(ReadRaw)

    TEST_CASES_BEGIN(ReadRawConstBuffer)
    TEST_CASES_END(ReadRawConstBuffer)

    TEST_CASES_BEGIN(WriteRaw)
    TEST_CASES_END(WriteRaw)

    TEST_CASES_BEGIN(WriteRawConst)
    TEST_CASES_END(WriteRawConst)

    TEST_CASES_BEGIN(GetLengthBits)

        TEST(Align1Byte)
        TEST(Align2Byte)
        TEST(Align3Byte)
        TEST(Align4Byte)

    TEST_CASES_END(GetLengthBits)

//    TEST(PullUpdatePush)
//    TEST(PullUpdatePush_Swap)

TEST_CASES_END(DataPacket_test)

//void initializeDp(DataPacket_test1& dp);

#endif
