#if !defined TEST_HPP
#define TEST_HPP

#include "Program.hpp"

class Test : public Program
{
public:

    Test(int argc, char** argv);

    virtual ~Test();

    bool run() = 0;

protected:

private:

};

#endif
