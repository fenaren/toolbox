// Endian.hpp
// Contains a utility function for determining the endianness of the host
// machine.

#if !defined ENDIAN_HPP
#define ENDIAN_HPP

namespace Endian
{
  enum Endianness
  {
    BIG,
    LITTLE
  };

  // Determines endianness of the host
  Endianness getEndianness();
};

#endif
