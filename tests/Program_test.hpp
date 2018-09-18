#ifndef PROGRAM_TEST_HPP
#define PROGRAM_TEST_HPP

#include "Test.hpp"

class Program_test : public Test
{
public:

    // Neither of these do anything
    Program_test();
    ~Program_test();

    // Implements the test
    virtual Test::Result run();
};

#endif
