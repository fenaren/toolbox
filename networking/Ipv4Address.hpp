#if !defined IPV4_ADDRESS_HPP
#define IPV4_ADDRESS_HPP

#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined DEBUG
#include <iostream>
#endif

#include "Data.hpp"

class Ipv4Address : public Data
{
public:

    // Constructs a new Ipv4Address, initialized to "0.0.0.0".
    Ipv4Address();

    // Constructs a new Ipv4Address, initialized to a copy of the raw address at
    // the indicated location.
    explicit Ipv4Address(unsigned char* buf);

    // Constructs a new Ipv4Address matching the given string representation.
    explicit Ipv4Address(const std::string& ipv4_address_str);

    // Copy constructor
    explicit Ipv4Address(const Ipv4Address& ipv4_address);

    // Destroys a Ipv4Address; does nothing, since this class doesn't
    // dynamically allocate memory.
    virtual ~Ipv4Address();

    virtual void read(unsigned char* buf);

    virtual void write(unsigned char* buf) const;

    // Allows a user to set a particular octet, numbered 0-3
    void setOctet(unsigned int octet, unsigned int value);

    // Allows a user to get the value of a particular octet, numbered 0-3
    unsigned int getOctet(unsigned int octet) const;

    // Defines how to convert a MacAddress to a std::string
    operator std::string() const;

    Ipv4Address& operator=(const std::string& ipv4_address_str);

    // IPv4 addresses are this many bytes long
    static const unsigned int LENGTH_BYTES = 4;

    // IPv4 address strings are this many characters long
    static const unsigned int MAX_STR_LENGTH_CHARS = 16;

    // Octets are represented raw as a single byte of data and so cannot have a
    // decimal value above this
    static const unsigned int MAX_OCTET_VALUE = 255;

private:

    unsigned int octets[LENGTH_BYTES];
};

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
