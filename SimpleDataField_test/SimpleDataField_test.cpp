#include <cstdint>
#include <iostream>
#include <list>

#include "SimpleDataField_test.hpp"

#include "SimpleDataField.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(SimpleDataField_test);

//==============================================================================
void SimpleDataField_test::addTestCases()
{
    ADD_TEST_CASE(Lengths);
    ADD_TEST_CASE(AssignmentGetValue);
    ADD_TEST_CASE(WriteRaw);
    ADD_TEST_CASE(ReadRaw);
}

//==============================================================================
Test::Result SimpleDataField_test::Lengths::body()
{
    SimpleDataField<char>               test_sdf_char(0);
    SimpleDataField<double>             test_sdf_double(0);
    SimpleDataField<float>              test_sdf_float(0);
    SimpleDataField<int>                test_sdf_int(0);
    SimpleDataField<long>               test_sdf_long(0);
    SimpleDataField<long double>        test_sdf_ld(0);
    SimpleDataField<long long>          test_sdf_ll(0);
    SimpleDataField<short>              test_sdf_short(0);
    SimpleDataField<unsigned char>      test_sdf_uc(0);
    SimpleDataField<unsigned int>       test_sdf_ui(0);
    SimpleDataField<unsigned long>      test_sdf_ul(0);
    SimpleDataField<unsigned long long> test_sdf_ull(0);
    SimpleDataField<unsigned short>     test_sdf_us(0);

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

    return Test::PASSED;
}

//==============================================================================
Test::Result SimpleDataField_test::AssignmentGetValue::body()
{
    SimpleDataField<char>               test_sdf_char(0);
    SimpleDataField<double>             test_sdf_double(0);
    SimpleDataField<float>              test_sdf_float(0);
    SimpleDataField<int>                test_sdf_int(0);
    SimpleDataField<long>               test_sdf_long(0);
    SimpleDataField<long double>        test_sdf_ld(0);
    SimpleDataField<long long>          test_sdf_ll(0);
    SimpleDataField<short>              test_sdf_short(0);
    SimpleDataField<unsigned char>      test_sdf_uc(0);
    SimpleDataField<unsigned int>       test_sdf_ui(0);
    SimpleDataField<unsigned long>      test_sdf_ul(0);
    SimpleDataField<unsigned long long> test_sdf_ull(0);
    SimpleDataField<unsigned short>     test_sdf_us(0);

    test_sdf_char   = 1;
    test_sdf_double = 2;
    test_sdf_float  = 3;
    test_sdf_int    = 4;
    test_sdf_long   = 5;
    test_sdf_ld     = 6;
    test_sdf_ll     = 7;
    test_sdf_short  = 8;
    test_sdf_uc     = 9;
    test_sdf_ui     = 10;
    test_sdf_ul     = 11;
    test_sdf_ull    = 12;
    test_sdf_us     = 13;

    MUST_BE_TRUE(test_sdf_char.getValue()   == 1);
    MUST_BE_TRUE(test_sdf_double.getValue() == 2);
    MUST_BE_TRUE(test_sdf_float.getValue()  == 3);
    MUST_BE_TRUE(test_sdf_int.getValue()    == 4);
    MUST_BE_TRUE(test_sdf_long.getValue()   == 5);
    MUST_BE_TRUE(test_sdf_ld.getValue()     == 6);
    MUST_BE_TRUE(test_sdf_ll.getValue()     == 7);
    MUST_BE_TRUE(test_sdf_short.getValue()  == 8);
    MUST_BE_TRUE(test_sdf_uc.getValue()     == 9);
    MUST_BE_TRUE(test_sdf_ui.getValue()     == 10);
    MUST_BE_TRUE(test_sdf_ul.getValue()     == 11);
    MUST_BE_TRUE(test_sdf_ull.getValue()    == 12);
    MUST_BE_TRUE(test_sdf_us.getValue()     == 13);

    return Test::PASSED;
}

//==============================================================================
Test::Result SimpleDataField_test::WriteRaw::body()
{
    SimpleDataField<char>               test_sdf_char(1);
    SimpleDataField<double>             test_sdf_double(2);
    SimpleDataField<float>              test_sdf_float(3);
    SimpleDataField<int>                test_sdf_int(4);
    SimpleDataField<long>               test_sdf_long(5);
    SimpleDataField<long double>        test_sdf_ld(6);
    SimpleDataField<long long>          test_sdf_ll(7);
    SimpleDataField<short>              test_sdf_short(8);
    SimpleDataField<unsigned char>      test_sdf_uc(9);
    SimpleDataField<unsigned int>       test_sdf_ui(10);
    SimpleDataField<unsigned long>      test_sdf_ul(11);
    SimpleDataField<unsigned long long> test_sdf_ull(12);
    SimpleDataField<unsigned short>     test_sdf_us(13);

    char               test_char   = 0;
    double             test_double = 0;
    float              test_float  = 0;
    int                test_int    = 0;
    long               test_long   = 0;
    long double        test_ld     = 0;
    long long          test_ll     = 0;
    short              test_short  = 0;
    unsigned char      test_uc     = 0;
    unsigned int       test_ui     = 0;
    unsigned long      test_ul     = 0;
    unsigned long long test_ull    = 0;
    unsigned short     test_us     = 0;

    test_sdf_char.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_char));
    // cppcheck-suppress invalidPointerCast
    test_sdf_double.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_double));
    // cppcheck-suppress invalidPointerCast
    test_sdf_float.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_float));
    test_sdf_int.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_int));
    test_sdf_long.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_long));
    // cppcheck-suppress invalidPointerCast
    test_sdf_ld.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ld));
    test_sdf_ll.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ll));
    test_sdf_short.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_short));
    test_sdf_uc.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_uc));
    test_sdf_ui.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ui));
    test_sdf_ul.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_ul));
    test_sdf_ull.DataField::writeRaw(
        reinterpret_cast<std::uint8_t*>(&test_ull));
    test_sdf_us.DataField::writeRaw(reinterpret_cast<std::uint8_t*>(&test_us));

    MUST_BE_TRUE(test_char   == 1);
    MUST_BE_TRUE(test_double == 2);
    MUST_BE_TRUE(test_float  == 3);
    MUST_BE_TRUE(test_int    == 4);
    MUST_BE_TRUE(test_long   == 5);
    MUST_BE_TRUE(test_ld     == 6);
    MUST_BE_TRUE(test_ll     == 7);
    MUST_BE_TRUE(test_short  == 8);
    MUST_BE_TRUE(test_uc     == 9);
    MUST_BE_TRUE(test_ui     == 10);
    MUST_BE_TRUE(test_ul     == 11);
    MUST_BE_TRUE(test_ull    == 12);
    MUST_BE_TRUE(test_us     == 13);

    return Test::PASSED;
}

//==============================================================================
Test::Result SimpleDataField_test::ReadRaw::body()
{
    SimpleDataField<char>               test_sdf_char(0);
    SimpleDataField<double>             test_sdf_double(0);
    SimpleDataField<float>              test_sdf_float(0);
    SimpleDataField<int>                test_sdf_int(0);
    SimpleDataField<long>               test_sdf_long(0);
    SimpleDataField<long double>        test_sdf_ld(0);
    SimpleDataField<long long>          test_sdf_ll(0);
    SimpleDataField<short>              test_sdf_short(0);
    SimpleDataField<unsigned char>      test_sdf_uc(0);
    SimpleDataField<unsigned int>       test_sdf_ui(0);
    SimpleDataField<unsigned long>      test_sdf_ul(0);
    SimpleDataField<unsigned long long> test_sdf_ull(0);
    SimpleDataField<unsigned short>     test_sdf_us(0);

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

    MUST_BE_TRUE(test_sdf_char.getValue()   == 1);
    MUST_BE_TRUE(test_sdf_double.getValue() == 2);
    MUST_BE_TRUE(test_sdf_float.getValue()  == 3);
    MUST_BE_TRUE(test_sdf_int.getValue()    == 4);
    MUST_BE_TRUE(test_sdf_long.getValue()   == 5);
    MUST_BE_TRUE(test_sdf_ld.getValue()     == 6);
    MUST_BE_TRUE(test_sdf_ll.getValue()     == 7);
    MUST_BE_TRUE(test_sdf_short.getValue()  == 8);
    MUST_BE_TRUE(test_sdf_uc.getValue()     == 9);
    MUST_BE_TRUE(test_sdf_ui.getValue()     == 10);
    MUST_BE_TRUE(test_sdf_ul.getValue()     == 11);
    MUST_BE_TRUE(test_sdf_ull.getValue()    == 12);
    MUST_BE_TRUE(test_sdf_us.getValue()     == 13);

    return Test::PASSED;
}
