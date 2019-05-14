#if !defined DATA_PACKET_TEST
#define DATA_PACKET_TEST

#include "DataPacket_test1.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(DataPacket_test)

    TEST(GetLengthBytes_Align1Byte)
    TEST(GetLengthBytes_Align2Byte)
    TEST(GetLengthBytes_Align3Byte)
    TEST(GetLengthBytes_Align4Byte)
    TEST(PullUpdatePush)
    TEST(PullUpdatePush_Swap)

TEST_CASES_END(DataPacket_test)

void initializeDp(DataPacket_test1& dp);

#endif
