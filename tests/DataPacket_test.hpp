#ifndef DATA_PACKET_TEST_HPP
#define DATA_PACKET_TEST_HPP

#include "TestCases.hpp"

#include "DataPacket_test_case1.hpp"
#include "DataPacket_test_case2.hpp"
#include "DataPacket_test_case3.hpp"

class DataPacket_test : public TestCases
{
public:

    // Neither of these do anything
    DataPacket_test();
    ~DataPacket_test();

    virtual void addTestCases();

private:

    DataPacket_test_case1 dptc1;
    DataPacket_test_case2 dptc2;
    DataPacket_test_case3 dptc3;
};

#endif
