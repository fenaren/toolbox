#ifndef SIMPLE_FIELD_TEST_HPP
#define SIMPLE_FIELD_TEST_HPP

#include "Test.hpp"

class SimpleDataField_test : public Test
{
public:

    // Neither of these do anything
    SimpleDataField_test();
    ~SimpleDataField_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
