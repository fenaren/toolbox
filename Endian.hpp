// Endian.hpp
// Contains a utility function for determining the endianness of the host
// machine.

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
