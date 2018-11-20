#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_HEADER(TCPSocket_test_case1);
TEST_HEADER(TCPSocket_test_case2);

TRIVIAL_TEST_CASES(TCPSocket_test);

//==============================================================================
void TCPSocket_test::addTestCases()
{
    addTestCase(new TCPSocket_test_case1());
    addTestCase(new TCPSocket_test_case2());
}
