#include <iostream>

#include "SimpleField_test.hpp"

#include "SimpleField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(SimpleField_test);

//==============================================================================
SimpleField_test::SimpleField_test()
{
}

//==============================================================================
SimpleField_test::~SimpleField_test()
{
}

//==============================================================================
Test::Result SimpleField_test::run()
{
    // Try to construct all the explicit instantiations
    SimpleField<char> test_sf_char("test_sf_char");
    SimpleField<double> test_sf_double("test_sf_double");
    SimpleField<float> test_sf_float("test_sf_float");
    SimpleField<int> test_sf_int("test_sf_int");
    SimpleField<long> test_sf_long("test_sf_long");
    SimpleField<long double> test_sf_ld("test_sf_ld");
    SimpleField<long long> test_sf_ll("test_sf_ll");
    SimpleField<short> test_sf_short("test_sf_short");
    SimpleField<unsigned char> test_sf_uc("test_sf_uc");
    SimpleField<unsigned int> test_sf_ui("test_sf_ui");
    SimpleField<unsigned long> test_sf_ul("test_sf_ul");
    SimpleField<unsigned long long> test_sf_ull("test_sf_ull");
    SimpleField<unsigned short> test_sf_us("test_sf_us");

    return Test::PASSED;
}
