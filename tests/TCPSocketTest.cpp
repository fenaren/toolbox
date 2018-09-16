#include "TCPSocketTest.hpp"

#include "TCPSocketTest_case1.hpp"
#include "TCPSocketTest_case2.hpp"
#include "TestCases.hpp"
#include "TestProgramMain.hpp"

TEST_PROGRAM_MAIN(TCPSocketTest);

//==============================================================================
TCPSocketTest::TCPSocketTest()
{
}

//==============================================================================
TCPSocketTest::~TCPSocketTest()
{
}

//==============================================================================
void TCPSocketTest::addTestCases()
{
    addTestCase(&case1);
    addTestCase(&case2);
}
