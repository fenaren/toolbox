// endian.cpp
// Contains a utility function for determining the endianness of the host
// machine.

#include "endian.hpp"

namespace Endian
{
  // Determines endianness of the host
  Endianness getEndianness()
  {
    unsigned short test_var = 0xff00;
    if (*(unsigned char*)&test_var > 0)
    {
      return BIG;
    }
    else
    {
      return LITTLE;
    }
  }
};
