#include <iostream>
#include <stdexcept>

#include "RawSocket.hpp"

int main(int argc, char** argv)
{
    int return_code = 0;

    try
    {
        // This won't work unless run as root, and I haven't figured out how to
        // make this work in an automated testing environment yet
        RawSocket raw_socket;
    }
    catch (std::runtime_error ex)
    {
        // This will happen if this test is run in an environment where raw
        // sockets are not permitted.  In this case return 2, which indicates
        // this test is skipped.
        return_code = 2;
    }

    return return_code;
}
