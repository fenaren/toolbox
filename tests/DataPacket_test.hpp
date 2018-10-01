#ifndef DATA_PACKET_TEST_HPP
#define DATA_PACKET_TEST_HPP

#include "Test.hpp"

class DataPacket_test : public Test
{
public:

    // Neither of these do anything
    DataPacket_test();
    ~DataPacket_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
