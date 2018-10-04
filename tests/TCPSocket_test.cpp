#include "TCPSocket_test.hpp"

#include "TCPSocket_test_case1.hpp"
#include "TCPSocket_test_case2.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(TCPSocket_test);

//==============================================================================
TCPSocket_test::TCPSocket_test()
{
}

//==============================================================================
TCPSocket_test::~TCPSocket_test()
{
}

//==============================================================================
void TCPSocket_test::addTestCases()
{
    addTestCase(&case1);
    addTestCase(&case2);
}
