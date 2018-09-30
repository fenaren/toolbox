#include <iostream>

#include "SimpleField_test.hpp"

#include "SimpleField.hpp"
#include "Test.hpp"
#include "TestProgramMain.hpp"

TEST_PROGRAM_MAIN(SimpleField_test);

//==============================================================================
SimpleField_test::SimpleField_test()
{
}

//==============================================================================
SimpleField_test::~SimpleField_test()
{
}

//==============================================================================
Test::Result SimpleField_test::run()
{
    SimpleField<double> test_sf("sf1");
    return Test::PASSED;
}
