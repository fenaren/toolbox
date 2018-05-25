#if !defined MAC_ADDRESS_HPP
#define MAC_ADDRESS_HPP

#include <istream>
#include <ostream>
#include <string>
#include <vector>

class MacAddress : public std::vector<char>
{
  public:

    // Constructs a new MacAddress.
    MacAddress();

    // Constructs a new MacAddress matching the given string representation.
    explicit MacAddress(const char* mac_address_str);

    // Constructs a new MacAddress matching the given string representation.
    explicit MacAddress(const std::string& mac_address_str);

    // Copy constructor
    explicit MacAddress(const MacAddress& mac_address);

    // Destroys a MacAddress; does nothing, since this class doesn't dynamically
    // allocate memory.
    ~MacAddress();

    // Writes string representation of self to the given string
    bool toString(std::string& mac_address_str) const;

    MacAddress& operator=(const std::string& mac_address_str);

    // Compares for equality with the given MAC address string
    bool operator==(const std::string& mac_address_str) const;

    // Compares for inequality with the given MAC address string
    bool operator!=(const std::string& mac_address_str) const;

    // MAC addresses are this many bytes long
    static const unsigned short MAC_LENGTH = 6;

    // MAC address strings are this many characters long
    static const unsigned short MAC_STR_LENGTH = 18;

private:

    void initialize();
};

// Writes a string representation of this MAC address
std::ostream& operator<<(std::ostream& os, MacAddress& mac_address);

// Reads a string representation of this MAC address
std::istream& operator>>(std::istream& is, MacAddress& mac_address);

// Compares for equality with the given MAC address string
bool operator==(const std::string& mac_address_str,
                const MacAddress&  mac_address);

// Compares for inequality with the given MAC address string
bool operator!=(const std::string& mac_address_str,
                const MacAddress&  mac_address);

#endif
