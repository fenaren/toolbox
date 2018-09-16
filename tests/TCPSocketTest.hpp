#ifndef TCP_SOCKET_TEST_HPP
#define TCP_SOCKET_TEST_HPP

#include "TestCases.hpp"

#include "TCPSocketTest_case1.hpp"
#include "TCPSocketTest_case2.hpp"
#include "Test.hpp"

class TCPSocketTest : public TestCases
{
public:

    TCPSocketTest();
    ~TCPSocketTest();

    // Each of the test cases implementing this test are added here
    virtual void addTestCases();

private:

    TCPSocketTest_case1 case1;
    TCPSocketTest_case2 case2;
};

#endif
