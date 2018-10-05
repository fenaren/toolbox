// For functionality that has no obvious home elsewhere

#if !defined MISC_HPP
#define MISC_HPP

// BIG_ENDIAN and LITTLE_ENDIAN are defined on macOS for some reason or other.
// Get rid of that definition and replace with this one.

#if defined BIG_ENDIAN
#undef BIG_ENDIAN
#endif

#if defined LITTLE_ENDIAN
#undef LITTLE_ENDIAN
#endif

namespace misc
{
  enum ByteOrder
  {
    BIG_ENDIAN,
    LITTLE_ENDIAN
  };

  // Determines byte ordering (endianness) of the host
  ByteOrder getByteOrder();
};

#endif
