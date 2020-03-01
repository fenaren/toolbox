#include "ConfigurationFileProcessor_test.hpp"

#include "ConfigurationFileProcessor.hpp"
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
        FileProcessor file_processor;
        file_processor.process("config");
        return Test::PASSED;
    }

}
