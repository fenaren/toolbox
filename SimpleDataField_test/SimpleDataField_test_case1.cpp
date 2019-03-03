#include <cstdint>
#include <iostream>

#include "SimpleDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_HEADER(SimpleDataField_test_case1);
TEST_CONSTRUCTOR_DESTRUCTOR(SimpleDataField_test_case1);

//==============================================================================
Test::Result SimpleDataField_test_case1::body()
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

    test_sdf_char.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_char2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_double.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_double2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_float.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_float2));
    test_sdf_int.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_int2));
    test_sdf_long.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_long2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_ld.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ld2));
    test_sdf_ll.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ll2));
    test_sdf_short.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_short2));
    test_sdf_uc.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_uc2));
    test_sdf_ui.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ui2));
    test_sdf_ul.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ul2));
    test_sdf_ull.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_ull2));
    test_sdf_us.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_us2));

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

    test_sdf_char.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_char));
    // cppcheck-suppress invalidPointerCast
    test_sdf_double.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_double));
    // cppcheck-suppress invalidPointerCast
    test_sdf_float.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_float));
    test_sdf_int.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_int));
    test_sdf_long.DataField::readRaw(
        reinterpret_cast<std::uint8_t*>(&test_long));
    // cppcheck-suppress invalidPointerCast
    test_sdf_ld.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_ld));
    test_sdf_ll.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_ll));
    test_sdf_short.DataField::readRaw(
        reinterpret_cast<std::uint8_t*>(&test_short));
    test_sdf_uc.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_uc));
    test_sdf_ui.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_ui));
    test_sdf_ul.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_ul));
    test_sdf_ull.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_ull));
    test_sdf_us.DataField::readRaw(reinterpret_cast<std::uint8_t*>(&test_us));

    test_sdf_char.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_char2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_double.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_double2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_float.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_float2));
    test_sdf_int.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_int2));
    test_sdf_long.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_long2));
    // cppcheck-suppress invalidPointerCast
    test_sdf_ld.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ld2));
    test_sdf_ll.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ll2));
    test_sdf_short.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_short2));
    test_sdf_uc.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_uc2));
    test_sdf_ui.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ui2));
    test_sdf_ul.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ul2));
    test_sdf_ull.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_ull2));
    test_sdf_us.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_us2));

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
