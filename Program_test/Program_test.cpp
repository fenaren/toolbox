#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "HelloWorld.hpp"
#include "Program.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "TestProgram.hpp"

TRIVIAL_TEST(Program_test);

//==============================================================================
Test::Result Program_test::run()
{
    // We're going to construct some fake arguments to push into our HelloWorld
    // test program

    // Three arguments total
    const int ARGC = 3;

    // Fill in the three arguments
    char* argv[ARGC];
    char zero[] = {"zero"};
    char one[] = {"one"};
    char two[] = {"two"};
    argv[0] = zero;
    argv[1] = one;
    argv[2] = two;

    // Normally a Program would get a proper set of arguments
    HelloWorld hello_world(ARGC, argv);

    // The first argument should have been stored as the name
    std::string name;
    hello_world.getName(name);
    MUST_BE_TRUE(name == zero);

    // The rest of the arguments should have been stored as actual arguments
    std::vector<std::string> arguments;
    hello_world.getArguments(arguments);
    for (std::vector<std::string>::iterator i = arguments.begin();
         i != arguments.end();
         ++i)
    {
        MUST_BE_TRUE(argv[std::distance(arguments.begin(), i) + 1] == *i);
    }

    // Running hello world has to be successful
    MUST_BE_TRUE(hello_world.run() == 0);

    return Test::PASSED;
}
