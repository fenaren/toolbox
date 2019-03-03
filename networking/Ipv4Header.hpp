#if !defined IPV4_HEADER_HPP
#define IPV4_HEADER_HPP

#include <cstdint>

#include "DataPacket.hpp"
#include "Ipv4Address.hpp"
#include "SimpleDataField.hpp"

// Represents an IPv4 header.  Optional options fields not supported; only
// fields through the destination IP address are supported.
class Ipv4Header : public DataPacket
{
public:

    Ipv4Header();
    virtual ~Ipv4Header();

    // Reads this data packet from the "buffer" memory location.  Each field
    // will be byteswapped if its source byte order does not match the byte
    // ordering of the host.  This function is modified from the base class to
    // break out the bitfields.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order);

    // Writes this data packet to the "buffer" memory location.  Each field will
    // be byteswapped if its source byte order does not match the byte ordering
    // of the host.  This version is modified from the base class to break out
    // the bitfields.
    virtual unsigned long writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order) const;

private:

    virtual void addDataFields();

    // Some header fields are not stored here in "raw" form because their raw
    // form has some non-standard size and isn't easily usable.  For example
    // when stored raw the version field is a 4-bit unsigned integer.

    unsigned int version; // 4-bit unsigned integer when raw
    unsigned int ihl;     // 4-bit unsigned integer when raw
    unsigned int dscp;    // 6-bit unsigned integer when raw
    unsigned int ecn;     // 2-bit unsigned integer when raw

    SimpleDataField<std::uint16_t> total_length;
    SimpleDataField<std::uint16_t> identification;

    bool flags_reserved;       // 1-bit flag when raw
    bool flags_dont_fragment;  // 1-bit flag when raw
    bool flags_more_fragments; // 1-bit flag when raw

    unsigned int fragment_offset; // 13-bit unsigned integer when raw

    SimpleDataField<std::uint8_t>  time_to_live;
    SimpleDataField<std::uint8_t>  protocol;
    SimpleDataField<std::uint16_t> header_checksum;

    Ipv4Address ip_address_source;
    Ipv4Address ip_address_destination;

    // Copy construction and assignment not allowed
    Ipv4Header(const Ipv4Header&);
    Ipv4Header& operator=(const Ipv4Header&);
};

#endif
