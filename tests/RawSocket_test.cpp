#include <stdexcept>

#include "RawSocket_test.hpp"

#include "RawSocket.hpp"
#include "Test.hpp"
#include "TestProgramMain.hpp"

TEST_PROGRAM_MAIN(RawSocket_test);

//==============================================================================
RawSocket_test::RawSocket_test()
{
}

//==============================================================================
RawSocket_test::~RawSocket_test()
{
}

//==============================================================================
Test::Result RawSocket_test::run()
{
    try
    {
        // This won't work unless run as root, and I haven't figured out how to
        // make this work in an automated testing environment yet
        RawSocket raw_socket;
    }
    catch (std::runtime_error ex)
    {
        // This will happen if this test is run in an environment where raw
        // sockets are not permitted.
        return Test::SKIPPED;
    }

    return Test::PASSED;
}
