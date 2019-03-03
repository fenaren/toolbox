#include "Ipv4Header.hpp"

#include "misc.hpp"

//==============================================================================
Ipv4Header::Ipv4Header() :
    version(0),
    ihl(0),
    dscp(0),
    ecn(0),
    flags_reserved(false),
    flags_dont_fragment(false),
    flags_more_fragments(false),
    fragment_offset(0)
{
}

//==============================================================================
Ipv4Header::~Ipv4Header()
{
}

//==============================================================================
unsigned long Ipv4Header::readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order)
{
}

//==============================================================================
unsigned long Ipv4Header::writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order) const
{
}

//==============================================================================
void Ipv4Header::addDataFields()
{
}
