#include "Ipv4Header.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TRIVIAL_TEST(Ipv4Header_test);

//==============================================================================
Test::Result Ipv4Header_test::run()
{
    Ipv4Header ipv4_header;
    return Test::PASSED;
}
