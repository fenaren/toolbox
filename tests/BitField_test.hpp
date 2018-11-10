#ifndef BIT_FIELD_TEST_HPP
#define BIT_FIELD_TEST_HPP

#include "Test.hpp"

class BitField_test : public Test
{
public:

    // Neither of these do anything
    BitField_test();
    ~BitField_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
