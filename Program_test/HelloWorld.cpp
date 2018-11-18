#include <iostream>

#include "HelloWorld.hpp"

#include "Program.hpp"

//==============================================================================
HelloWorld::HelloWorld(int argc, char** argv) :
    Program(argc, argv)
{
}

//==============================================================================
HelloWorld::~HelloWorld()
{
}

//==============================================================================
int HelloWorld::run()
{
    std::cout << "Hello world\n";
    return 0;
}
