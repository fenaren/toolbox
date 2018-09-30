#ifndef SIMPLE_FIELD_TEST_HPP
#define SIMPLE_FIELD_TEST_HPP

#include "Test.hpp"

class SimpleField_test : public Test
{
public:

    // Neither of these do anything
    SimpleField_test();
    ~SimpleField_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
