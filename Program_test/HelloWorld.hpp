#if !defined HELLO_WORLD_HPP
#define HELLO_WORLD_HPP

#include "Program.hpp"

// Does nothing but print "hello world".  This class is not meant to be used
// outside this test.  It exists to be exercised during the test and nothing
// more.
class HelloWorld : public Program
{
public:

    HelloWorld(int argc, char** argv);
    virtual ~HelloWorld();
    virtual int run();
};

#endif
