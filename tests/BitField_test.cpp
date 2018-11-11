#include "BitField_test.hpp"

#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(BitField_test);
TEST_CONSTRUCTOR_DESTRUCTOR(BitField_test);

//==============================================================================
void BitField_test::addTestCases()
{
    addTestCase(&case1);
    addTestCase(&case2);
}
