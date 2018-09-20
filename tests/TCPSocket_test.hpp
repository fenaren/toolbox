#ifndef TCP_SOCKET_TEST_HPP
#define TCP_SOCKET_TEST_HPP

#include "TestCases.hpp"

#include "TCPSocket_test_case1.hpp"
#include "TCPSocket_test_case2.hpp"
#include "Test.hpp"

class TCPSocket_test : public TestCases
{
public:

    // Neither of these do anything
    TCPSocket_test();
    ~TCPSocket_test();

    // Each of the test cases implementing this test are added here
    virtual void addTestCases();

private:

    TCPSocket_test_case1 case1;
    TCPSocket_test_case2 case2;
};

#endif
