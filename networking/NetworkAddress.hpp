#if !defined NETWORK_ADDRESS_HPP
#define NETWORK_ADDRESS_HPP

#include <stdexcept>

#include "Field.hpp"

class NetworkAddress : public Field
{
public:

    // Will dynamically allocate an address that is "length_bytes" in size
    NetworkAddress(unsigned int length_bytes);

    // Will use the memory at "buffer" (of size "length_bytes") as the raw
    // network address; will not dynamically allocate memory
    NetworkAddress(unsigned char* buffer,
                   unsigned int   length_bytes);

    virtual ~NetworkAddress();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Octet access and mutation
    unsigned char getOctet(unsigned int octet) const;
    void setOctet(unsigned int octet, unsigned char value);

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    NetworkAddress& operator=(const NetworkAddress& network_address);

private:

    // Raw network address is stored at this location
    unsigned char* network_address_raw;

    // Raw network address is this many bytes in length
    unsigned int length_bytes;

    // Does this class own the memory at "network_address_raw"?
    bool network_address_raw_owned;
};

inline unsigned char NetworkAddress::getOctet(unsigned int octet) const
{
    if (octet >= length_bytes)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    return network_address_raw[octet];
}

inline void NetworkAddress::setOctet(unsigned int octet, unsigned char value)
{
    if (octet >= length_bytes)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    network_address_raw[octet] = value;
}

inline unsigned int NetworkAddress::getLengthBytes() const
{
    return length_bytes;
}

bool operator==(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2);

bool operator!=(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2);

#endif
