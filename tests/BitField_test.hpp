#ifndef BIT_FIELD_TEST_HPP
#define BIT_FIELD_TEST_HPP

#include "TestCases.hpp"

#include "TestMacros.hpp"

TEST_HEADER(BitField_test_case1);
TEST_HEADER(BitField_test_case2);

class BitField_test : public TestCases
{
public:

    // Neither of these do anything
    BitField_test();
    ~BitField_test();

    // Each of the test cases implementing this test are added here
    virtual void addTestCases();

private:

    BitField_test_case1 case1;
    BitField_test_case2 case2;
};

#endif
