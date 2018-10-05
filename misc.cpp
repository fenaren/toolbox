#include "misc.hpp"

namespace misc
{
  // Determines byte ordering (endianness) of the host
  ByteOrder getByteOrder()
  {
    unsigned short test_var = 0xff00;
    if (*(unsigned char*)&test_var > 0)
    {
      return BIG_ENDIAN;
    }
    else
    {
      return LITTLE_ENDIAN;
    }
  }
};
