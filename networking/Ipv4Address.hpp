#if !defined IPV4_ADDRESS_HPP
#define IPV4_ADDRESS_HPP

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "Field.hpp"

class Ipv4Address : public Field
{
public:

    // Constructs a new Ipv4Address, initialized to "0.0.0.0".
    Ipv4Address();

    // Constructs a new Ipv4Address, initialized to a copy of the raw address at
    // the indicated location.
    explicit Ipv4Address(const unsigned char* raw_address);

    // Constructs a new Ipv4Address matching the given string representation.
    explicit Ipv4Address(const std::string& ipv4_address_str);

    // Copy constructor
    explicit Ipv4Address(const Ipv4Address& ipv4_address);

    // Defines how to convert a MacAddress to a std::string
    operator std::string() const;

    // Destroys a Ipv4Address; does nothing, since this class doesn't
    // dynamically allocate memory.
    virtual ~Ipv4Address();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getSizeBytes() const;

    // Octet access and mutation
    unsigned char getOctet(unsigned int octet) const;
    void setOctet(unsigned int octet, unsigned char value);

    Ipv4Address& operator=(const std::string& ipv4_address_str);

    // IPv4 addresses are this many bytes long
    static const unsigned short LENGTH_BYTES = 4;

    // IPv4 address strings are this many characters long
    static const unsigned short MAX_STR_LENGTH_CHARS = 16;

private:

    unsigned char ipv4_address_raw[LENGTH_BYTES];
};

inline unsigned char Ipv4Address::getOctet(unsigned int octet) const
{
    if (octet >= LENGTH_BYTES)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    return ipv4_address_raw[octet];
}

inline void Ipv4Address::setOctet(unsigned int octet, unsigned char value)
{
    if (octet >= LENGTH_BYTES)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    ipv4_address_raw[octet] = value;
}

std::ostream& operator<<(std::ostream& os, const Ipv4Address& ipv4_address);

std::istream& operator>>(std::istream& is, Ipv4Address& ipv4_address);

bool operator==(const Ipv4Address& ipv4_address1,
                const Ipv4Address& ipv4_address2);
bool operator==(const Ipv4Address& ipv4_address1,
                const std::string& ipv4_address2);
bool operator==(const std::string& ipv4_address1,
                const Ipv4Address& ipv4_address2);

bool operator!=(const Ipv4Address& ipv4_address1,
                const Ipv4Address& ipv4_address2);
bool operator!=(const Ipv4Address& ipv4_address1,
                const std::string& ipv4_address2);
bool operator!=(const std::string& ipv4_address1,
                const Ipv4Address& ipv4_address2);

#endif
