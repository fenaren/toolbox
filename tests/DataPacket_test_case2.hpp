#ifndef DATA_PACKET_TEST_CASE2_HPP
#define DATA_PACKET_TEST_CASE2_HPP

#include "Test.hpp"

class DataPacket_test_case2 : public Test
{
public:

    // Neither of these do anything
    DataPacket_test_case2();
    ~DataPacket_test_case2();

    virtual Test::Result run();
};

#endif
