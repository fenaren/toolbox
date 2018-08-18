#include <iostream>
#include <stdexcept>

#include "RawSocket.hpp"

int main(int argc, char** argv)
{
    try
    {
        // This won't work unless run as root, and I haven't figured out how to
        // make this work in an automated testing environment yet
        RawSocket raw_socket;
    }
    catch (std::runtime_error ex)
    {
        // Ignore the exception if it happens, for now.  There isn't much power
        // in this unit test ... it can only really check that RawSocket can
        // compile into a program
        std::cout << "Runtime error from RawSocket constructor caught\n";
    }

    return 0;
}
