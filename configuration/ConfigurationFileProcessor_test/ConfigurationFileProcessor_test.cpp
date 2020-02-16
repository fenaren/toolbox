#include "ConfigurationFileProcessor_test.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::FileProcessor_test);

namespace Configuration
{

    //==========================================================================
    void FileProcessor_test::addTestCases()
    {
        ADD_TEST_CASE(Stub);
    }

    //==========================================================================
    Test::Result FileProcessor_test::Stub::body()
    {
        return Test::PASSED;
    }

}
