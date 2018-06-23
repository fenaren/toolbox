#if !defined IPV4_ADDRESS_HPP
#define IPV4_ADDRESS_HPP

#include <istream>
#include <ostream>
#include <string>
#include <vector>

class Ipv4Address : public std::vector<char>
{
  public:

    // Constructs a new Ipv4Address.
    Ipv4Address();

    // Constructs a new Ipv4Address matching the given string representation.
    explicit Ipv4Address(const char* ipv4_address_str);

    // Constructs a new Ipv4Address matching the given string representation.
    explicit Ipv4Address(const std::string& ipv4_address_str);

    // Copy constructor
    explicit Ipv4Address(const Ipv4Address& ipv4_address);

    // Destroys a Ipv4Address; does nothing, since this class doesn't
    // dynamically allocate memory.
    ~Ipv4Address();

    // Writes string representation of self to the given string
    bool toString(std::string& ipv4_address_str) const;

    Ipv4Address& operator=(const std::string& ipv4_address_str);

    // Compares for equality with the given IPv4 address string
    bool operator==(const std::string& ipv4_address_str) const;

    // Compares for inequality with the given IPv4 address string
    bool operator!=(const std::string& ipv4_address_str) const;

    // IPv4 addresses are this many bytes long
    static const unsigned short IPV4_LENGTH_BYTES = 4;

    // IPv4 address strings are this many characters long
    static const unsigned short IPV4_MAX_STR_LENGTH_CHARS = 15;

private:

    void initialize();
};

// Writes a string representation of this IPv4 address
std::ostream& operator<<(std::ostream& os, Ipv4Address& ipv4_address);

// Reads a string representation of this IPv4 address
std::istream& operator>>(std::istream& is, Ipv4Address& ipv4_address);

// Compares for equality with the given IPv4 address string
bool operator==(const std::string& ipv4_address_str,
                const Ipv4Address& ipv4_address);

// Compares for inequality with the given IPv4 address string
bool operator!=(const std::string& ipv4_address_str,
                const Ipv4Address& ipv4_address);

#endif
