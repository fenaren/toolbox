#include "ConfigurationListParameter_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::ListParameter_test);

namespace Configuration
{

    //==========================================================================
    void ListParameter_test::addTestCases()
    {
        ADD_TEST_CASE(Stub);
    }

    //==========================================================================
    Test::Result ListParameter_test::Stub::body()
    {
        return Test::PASSED;
    }

}
