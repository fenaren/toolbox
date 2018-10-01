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

    MUST_BE_TRUE(test_sf_char.getLengthBytes()   == sizeof(char));
    MUST_BE_TRUE(test_sf_double.getLengthBytes() == sizeof(double));
    MUST_BE_TRUE(test_sf_float.getLengthBytes()  == sizeof(float));
    MUST_BE_TRUE(test_sf_int.getLengthBytes()    == sizeof(int));
    MUST_BE_TRUE(test_sf_long.getLengthBytes()   == sizeof(long));
    MUST_BE_TRUE(test_sf_ld.getLengthBytes()     == sizeof(long double));
    MUST_BE_TRUE(test_sf_ll.getLengthBytes()     == sizeof(long long));
    MUST_BE_TRUE(test_sf_short.getLengthBytes()  == sizeof(short));
    MUST_BE_TRUE(test_sf_uc.getLengthBytes()     == sizeof(unsigned char));
    MUST_BE_TRUE(test_sf_ui.getLengthBytes()     == sizeof(unsigned int));
    MUST_BE_TRUE(test_sf_ul.getLengthBytes()     == sizeof(unsigned long));
    MUST_BE_TRUE(test_sf_ull.getLengthBytes()    == sizeof(unsigned long long));
    MUST_BE_TRUE(test_sf_us.getLengthBytes()     == sizeof(unsigned short));

    char               test_char   = 1;
    double             test_double = 2;
    float              test_float  = 3;
    int                test_int    = 4;
    long               test_long   = 5;
    long double        test_ld     = 6;
    long long          test_ll     = 7;
    short              test_short  = 8;
    unsigned char      test_uc     = 9;
    unsigned int       test_ui     = 10;
    unsigned long      test_ul     = 11;
    unsigned long long test_ull    = 12;
    unsigned short     test_us     = 13;

    test_sf_char   = test_char;
    test_sf_double = test_double;
    test_sf_float  = test_float;
    test_sf_int    = test_int;
    test_sf_long   = test_long;
    test_sf_ld     = test_ld;
    test_sf_ll     = test_ll;
    test_sf_short  = test_short;
    test_sf_uc     = test_uc;
    test_sf_ui     = test_ui;
    test_sf_ul     = test_ul;
    test_sf_ull    = test_ull;
    test_sf_us     = test_us;

    char               test_char2;
    double             test_double2;
    float              test_float2;
    int                test_int2;
    long               test_long2;
    long double        test_ld2;
    long long          test_ll2;
    short              test_short2;
    unsigned char      test_uc2;
    unsigned int       test_ui2;
    unsigned long      test_ul2;
    unsigned long long test_ull2;
    unsigned short     test_us2;

    test_sf_char.writeRaw(reinterpret_cast<unsigned char*>(&test_char2));
    // cppcheck-suppress invalidPointerCast
    test_sf_double.writeRaw(reinterpret_cast<unsigned char*>(&test_double2));
    // cppcheck-suppress invalidPointerCast
    test_sf_float.writeRaw(reinterpret_cast<unsigned char*>(&test_float2));
    test_sf_int.writeRaw(reinterpret_cast<unsigned char*>(&test_int2));
    test_sf_long.writeRaw(reinterpret_cast<unsigned char*>(&test_long2));
    // cppcheck-suppress invalidPointerCast
    test_sf_ld.writeRaw(reinterpret_cast<unsigned char*>(&test_ld2));
    test_sf_ll.writeRaw(reinterpret_cast<unsigned char*>(&test_ll2));
    test_sf_short.writeRaw(reinterpret_cast<unsigned char*>(&test_short2));
    test_sf_uc.writeRaw(reinterpret_cast<unsigned char*>(&test_uc2));
    test_sf_ui.writeRaw(reinterpret_cast<unsigned char*>(&test_ui2));
    test_sf_ul.writeRaw(reinterpret_cast<unsigned char*>(&test_ul2));
    test_sf_ull.writeRaw(reinterpret_cast<unsigned char*>(&test_ull2));
    test_sf_us.writeRaw(reinterpret_cast<unsigned char*>(&test_us2));

    MUST_BE_TRUE(test_char   == test_char2);
    MUST_BE_TRUE(test_double == test_double2);
    MUST_BE_TRUE(test_float  == test_float2);
    MUST_BE_TRUE(test_int    == test_int2);
    MUST_BE_TRUE(test_long   == test_long2);
    MUST_BE_TRUE(test_ld     == test_ld2);
    MUST_BE_TRUE(test_ll     == test_ll2);
    MUST_BE_TRUE(test_short  == test_short2);
    MUST_BE_TRUE(test_uc     == test_uc2);
    MUST_BE_TRUE(test_ui     == test_ui2);
    MUST_BE_TRUE(test_ul     == test_ul2);
    MUST_BE_TRUE(test_ull    == test_ull2);
    MUST_BE_TRUE(test_us     == test_us2);

    return Test::PASSED;
}
