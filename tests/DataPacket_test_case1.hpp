#ifndef DATA_PACKET_TEST_CASE1_HPP
#define DATA_PACKET_TEST_CASE1_HPP

#include "Test.hpp"

class DataPacket_test_case1 : public Test
{
public:

    // Neither of these do anything
    DataPacket_test_case1();
    ~DataPacket_test_case1();

    virtual Test::Result run();
};

#endif
