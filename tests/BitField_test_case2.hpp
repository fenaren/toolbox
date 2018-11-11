#ifndef BITFIELD_TEST_CASE2_HPP
#define BITFIELD_TEST_CASE2_HPP

#include "Test.hpp"

class BitField;

class BitField_test_case2 : public Test
{
public:

    // Neither of these do anything
    BitField_test_case2();
    ~BitField_test_case2();

    // Implements the test
    virtual Test::Result run();

private:

    template<class T>
    bool tryAllBits(BitField& bitfield, T& raw_bitfield);
};

#endif
