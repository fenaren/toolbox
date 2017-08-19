#include <iostream>

#include "Log.hpp"

int main (int argc, char** argv)
{
    Log log;
    log.write("message1");
    log.writeWarning("message2");
    log.writeError("message3");

    log.useLocalTime();
    log.write("message1");
    log.writeWarning("message2");
    log.writeError("message3");

    return 0;
}
