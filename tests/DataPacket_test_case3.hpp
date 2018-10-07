#ifndef DATA_PACKET_TEST_CASE3_HPP
#define DATA_PACKET_TEST_CASE3_HPP

#include "Test.hpp"

class DataPacket_test_case3 : public Test
{
public:

    // Neither of these do anything
    DataPacket_test_case3();
    ~DataPacket_test_case3();

    virtual Test::Result run();
};

#endif
