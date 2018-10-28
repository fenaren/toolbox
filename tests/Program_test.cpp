#include <iostream>

#include "Program_test.hpp"

#include "Program.hpp"
#include "Program_test_tc1.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "TestProgram.hpp"

TEST_PROGRAM_MAIN(Program_test);

//==============================================================================
Program_test::Program_test()
{
}

//==============================================================================
Program_test::~Program_test()
{
}

//==============================================================================
Test::Result Program_test::run()
{
    // Normally a Program would get a proper set of arguments
    Program_test_tc1 program_ut(0, 0);

    std::string name;
    program_ut.getName(name);
    std::cout << name << "\n";

    std::vector<std::string> arguments;
    program_ut.getArguments(arguments);
    for (std::vector<std::string>::const_iterator i = arguments.begin();
         i != arguments.end();
         ++i)
    {
        std::cout << *i << "\n";
    }

    return Test::PASSED;
}
