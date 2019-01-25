#include <cstdint>
#include <iostream>

#include "SimpleDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TEST_HEADER(SimpleDataField_test_case2);
TEST_CONSTRUCTOR_DESTRUCTOR(SimpleDataField_test_case2);

//==============================================================================
Test::Result SimpleDataField_test_case2::body()
{
    SimpleDataField<unsigned char> test_sdf_uchar(255);

    std::uint8_t destbuf[2];
    memset(destbuf, 0, 2);

    test_sdf_uchar.writeRaw(destbuf, misc::getByteOrder(), 8);

    std::cout << static_cast<unsigned int>(destbuf[0]) << " "
              << static_cast<unsigned int>(destbuf[1]) << "\n";

    return Test::PASSED;
}
