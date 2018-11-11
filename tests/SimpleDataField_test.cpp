#include <iostream>

#include "SimpleDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TRIVIAL_TEST(SimpleDataField_test);

//==============================================================================
Test::Result SimpleDataField_test::run()
{
    // Try to construct all the explicit instantiations
    SimpleDataField<char> test_sdf_char;
    SimpleDataField<double> test_sdf_double;
    SimpleDataField<float> test_sdf_float;
    SimpleDataField<int> test_sdf_int;
    SimpleDataField<long> test_sdf_long;
    SimpleDataField<long double> test_sdf_ld;
    SimpleDataField<long long> test_sdf_ll;
    SimpleDataField<short> test_sdf_short;
    SimpleDataField<unsigned char> test_sdf_uc;
    SimpleDataField<unsigned int> test_sdf_ui;
    SimpleDataField<unsigned long> test_sdf_ul;
    SimpleDataField<unsigned long long> test_sdf_ull;
    SimpleDataField<unsigned short> test_sdf_us;

    MUST_BE_TRUE(test_sdf_char.getLengthBytes()   == sizeof(char));
    MUST_BE_TRUE(test_sdf_double.getLengthBytes() == sizeof(double));
    MUST_BE_TRUE(test_sdf_float.getLengthBytes()  == sizeof(float));
    MUST_BE_TRUE(test_sdf_int.getLengthBytes()    == sizeof(int));
    MUST_BE_TRUE(test_sdf_long.getLengthBytes()   == sizeof(long));
    MUST_BE_TRUE(test_sdf_ld.getLengthBytes()     == sizeof(long double));
    MUST_BE_TRUE(test_sdf_ll.getLengthBytes()     == sizeof(long long));
    MUST_BE_TRUE(test_sdf_short.getLengthBytes()  == sizeof(short));
    MUST_BE_TRUE(test_sdf_uc.getLengthBytes()     == sizeof(unsigned char));
    MUST_BE_TRUE(test_sdf_ui.getLengthBytes()     == sizeof(unsigned int));
    MUST_BE_TRUE(test_sdf_ul.getLengthBytes()     == sizeof(unsigned long));
    MUST_BE_TRUE(test_sdf_ull.getLengthBytes()    == sizeof(unsigned long long));
    MUST_BE_TRUE(test_sdf_us.getLengthBytes()     == sizeof(unsigned short));

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

    test_sdf_char   = test_char;
    test_sdf_double = test_double;
    test_sdf_float  = test_float;
    test_sdf_int    = test_int;
    test_sdf_long   = test_long;
    test_sdf_ld     = test_ld;
    test_sdf_ll     = test_ll;
    test_sdf_short  = test_short;
    test_sdf_uc     = test_uc;
    test_sdf_ui     = test_ui;
    test_sdf_ul     = test_ul;
    test_sdf_ull    = test_ull;
    test_sdf_us     = test_us;

    MUST_BE_TRUE(static_cast<int>(test_sdf_int) == 4);

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

    test_sdf_char.writeRaw(reinterpret_cast<unsigned char*>(&test_char2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_double.writeRaw(reinterpret_cast<unsigned char*>(&test_double2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_float.writeRaw(reinterpret_cast<unsigned char*>(&test_float2));
    test_sdf_int.writeRaw(reinterpret_cast<unsigned char*>(&test_int2));
    test_sdf_long.writeRaw(reinterpret_cast<unsigned char*>(&test_long2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_ld.writeRaw(reinterpret_cast<unsigned char*>(&test_ld2));
    test_sdf_ll.writeRaw(reinterpret_cast<unsigned char*>(&test_ll2));
    test_sdf_short.writeRaw(reinterpret_cast<unsigned char*>(&test_short2));
    test_sdf_uc.writeRaw(reinterpret_cast<unsigned char*>(&test_uc2));
    test_sdf_ui.writeRaw(reinterpret_cast<unsigned char*>(&test_ui2));
    test_sdf_ul.writeRaw(reinterpret_cast<unsigned char*>(&test_ul2));
    test_sdf_ull.writeRaw(reinterpret_cast<unsigned char*>(&test_ull2));
    test_sdf_us.writeRaw(reinterpret_cast<unsigned char*>(&test_us2));

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

    test_char++;
    test_double++;
    test_float++;
    test_int++;
    test_long++;
    test_ld++;
    test_ll++;
    test_short++;
    test_uc++;
    test_ui++;
    test_ul++;
    test_ull++;
    test_us++;

    test_sdf_char.readRaw(reinterpret_cast<unsigned char*>(&test_char));
    // cppcheck-suppress invalidPointerCast
    test_sdf_double.readRaw(reinterpret_cast<unsigned char*>(&test_double));
    // cppcheck-suppress invalidPointerCast
    test_sdf_float.readRaw(reinterpret_cast<unsigned char*>(&test_float));
    test_sdf_int.readRaw(reinterpret_cast<unsigned char*>(&test_int));
    test_sdf_long.readRaw(reinterpret_cast<unsigned char*>(&test_long));
    // cppcheck-suppress invalidPointerCast
    test_sdf_ld.readRaw(reinterpret_cast<unsigned char*>(&test_ld));
    test_sdf_ll.readRaw(reinterpret_cast<unsigned char*>(&test_ll));
    test_sdf_short.readRaw(reinterpret_cast<unsigned char*>(&test_short));
    test_sdf_uc.readRaw(reinterpret_cast<unsigned char*>(&test_uc));
    test_sdf_ui.readRaw(reinterpret_cast<unsigned char*>(&test_ui));
    test_sdf_ul.readRaw(reinterpret_cast<unsigned char*>(&test_ul));
    test_sdf_ull.readRaw(reinterpret_cast<unsigned char*>(&test_ull));
    test_sdf_us.readRaw(reinterpret_cast<unsigned char*>(&test_us));

    test_sdf_char.writeRaw(reinterpret_cast<unsigned char*>(&test_char2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_double.writeRaw(reinterpret_cast<unsigned char*>(&test_double2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_float.writeRaw(reinterpret_cast<unsigned char*>(&test_float2));
    test_sdf_int.writeRaw(reinterpret_cast<unsigned char*>(&test_int2));
    test_sdf_long.writeRaw(reinterpret_cast<unsigned char*>(&test_long2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_ld.writeRaw(reinterpret_cast<unsigned char*>(&test_ld2));
    test_sdf_ll.writeRaw(reinterpret_cast<unsigned char*>(&test_ll2));
    test_sdf_short.writeRaw(reinterpret_cast<unsigned char*>(&test_short2));
    test_sdf_uc.writeRaw(reinterpret_cast<unsigned char*>(&test_uc2));
    test_sdf_ui.writeRaw(reinterpret_cast<unsigned char*>(&test_ui2));
    test_sdf_ul.writeRaw(reinterpret_cast<unsigned char*>(&test_ul2));
    test_sdf_ull.writeRaw(reinterpret_cast<unsigned char*>(&test_ull2));
    test_sdf_us.writeRaw(reinterpret_cast<unsigned char*>(&test_us2));

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
