#include <iostream>
#include <string>

#include "ConfigurationListParameter_test.hpp"

#include "ConfigurationListParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::ListParameter_test);

//=============================================================================================
void Configuration::ListParameter_test::addTestCases()
{
    ADD_TEST_CASE(FromString);
    ADD_TEST_CASE(ToString);
}

//=============================================================================================
Test::Result Configuration::ListParameter_test::FromString::body()
{
    std::string source = "2 3 4 5";
    Configuration::ListParameter<unsigned int> undertest;
    undertest.fromString(source);

    std::list<unsigned int> asdf;
    undertest.getValue(asdf);

    undertest > undertest;

    for (std::list<unsigned int>::const_iterator i = asdf.begin();
         i != asdf.end();
         ++i)
    {
        std::cout << *i << "\n";
    }

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::ListParameter_test::ToString::body()
{
    return Test::PASSED;
}
