#include <cstring>
#include <new>

#include "NetworkAddress.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
// Dynamically allocates an address that is "length_bytes" in size.  Implies
// MemoryMode::MEMORY_INTERNAL.
//==============================================================================
NetworkAddress::NetworkAddress(unsigned int length_bytes) :
    DataField(),
    length_bytes(length_bytes),
    memory_mode(MEMORY_INTERNAL)
{
    network_address_raw = new unsigned char[length_bytes];
    memset(network_address_raw, 0, length_bytes);
}

//==============================================================================
// Behavior depends on the value of "memory_mode".  If "memory_mode" is
// MemoryMode::MEMORY_INTERNAL, the data at "buffer" of length "length_bytes"
// will be copied into dynamically-allocated memory internal to this class.  If
// "memory_mode" is MemoryMode::MEMORY_EXTERNAL, the data at "buffer" of length
// "length_bytes" will be used by this class in-place and no dynamic memory
// allocation will occur.  Uses the memory at "buffer" (of size "length_bytes")
// as the raw network address; does not dynamically allocate memory
//==============================================================================
NetworkAddress::NetworkAddress(unsigned char* buffer,
                               unsigned int   length_bytes,
                               MemoryMode     memory_mode) :
    DataField(),
    length_bytes(length_bytes),
    memory_mode(memory_mode)
{
    if (memory_mode == MEMORY_INTERNAL)
    {
        network_address_raw = new unsigned char[length_bytes];
        readRaw(buffer);
    }
    else
    {
        // "memory_mode" must equal EXTERNAL
        network_address_raw = buffer;
    }
}

//==============================================================================
// Copy constructor; will dynamically allocate memory for the
// "network_address_raw" stored in the new NetworkAddress.  Implies
// MemoryMode::MEMORY_INTERNAL.
//==============================================================================
NetworkAddress::NetworkAddress(const NetworkAddress& network_address) :
    DataField(),
    memory_mode(MEMORY_INTERNAL)
{
    length_bytes = network_address.getLengthBytes();

    network_address_raw = new unsigned char[length_bytes];

    network_address.writeRaw(network_address_raw);
}

//==============================================================================
// Frees the memory at "network_address_raw" if owned by this class
//==============================================================================
NetworkAddress::~NetworkAddress()
{
    if (memory_mode == MEMORY_INTERNAL)
    {
        delete[] network_address_raw;
    }
}

//==============================================================================
// Reads a raw network address from the "buffer" memory location without
// considering byte ordering.  Byte ordering has seemingly no relevance to
// network addresses (in the general sense of the term) anyway.
//==============================================================================
unsigned int NetworkAddress::readRaw(const unsigned char* buffer)
{
    return DataField::readRaw(buffer);
}

//==============================================================================
// Reads a raw network address from the "buffer" memory location.  This function
// is required by the framework to be implemented here, despite being
// functionally identical to the single-argument version defined above.  If byte
// ordering were relevant to network addresses (in the general sense of the
// term) this function would be where that difference would be handled.
//==============================================================================
unsigned int NetworkAddress::readRaw(const unsigned char* buffer,
                                     misc::ByteOrder      source_byte_order)
{
    // Byteswapping doesn't seem to be a relevant operation on network addresses
    // (in the general sense of the term) so no byteswapping happens here
    // regardless of the byte ordering of the source.
    memcpy(network_address_raw, buffer, length_bytes);
    return length_bytes;
}

//==============================================================================
// Writes a raw network address to the "buffer" memory location without
// considering byte ordering.  Byte ordering has seemingly no relevance to
// network addresses (in the general sense of the term) anyway.
//==============================================================================
unsigned int NetworkAddress::writeRaw(unsigned char* buffer) const
{
    return DataField::writeRaw(buffer);
}

//==============================================================================
// Writes a raw network address to the "buffer" memory location.  This function
// is required by the framework to be implemented here, despite being
// functionally identical to the single-argument version defined above.  If byte
// ordering were relevant to network addresses (in the general sense of the
// term) this function would be where that difference would be handled.
//==============================================================================
unsigned int
NetworkAddress::writeRaw(unsigned char*  buffer,
                         misc::ByteOrder destination_byte_order) const
{
    // No byteswapping regardless of "destination_byte_order" setting
    memcpy(buffer, network_address_raw, length_bytes);
    return length_bytes;
}

//==============================================================================
// Assigns a NetworkAddress to this NetworkAddress
//==============================================================================
NetworkAddress& NetworkAddress::operator=(const NetworkAddress& network_address)
{
    network_address.writeRaw(network_address_raw);
    return *this;
}

//==============================================================================
// Equality comparison, NetworkAddress == NetworkAddress
//==============================================================================
bool operator==(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2)
{
    if (network_address1.getLengthBytes() != network_address2.getLengthBytes())
    {
        return false;
    }

    // We know both addresses have equal length at this point
    unsigned int length_bytes = network_address1.getLengthBytes();

    for (unsigned int i = 0; i < length_bytes; i++)
    {
        if (network_address1.getOctet(i) != network_address2.getOctet(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
// Inequality comparison, NetworkAddress != NetworkAddress
//==============================================================================
bool operator!=(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2)
{
    return !(network_address1 == network_address2);
}
