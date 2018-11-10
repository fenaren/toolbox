#ifndef ETHERNET_II_HEADER_TEST_HPP
#define ETHERNET_II_HEADER_TEST_HPP

#include "Test.hpp"

class EthernetIIHeader_test : public Test
{
public:

    // Neither of these do anything
    EthernetIIHeader_test();
    ~EthernetIIHeader_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
