#ifndef LOG_UT_HPP
#define LOG_UT_HPP

#include "Program.hpp"

class LogUT : public Program
{
public:

    LogUT(int argc, char** argv);

    ~LogUT();

    // Implements the Log unit test
    virtual int run();
};

#endif
