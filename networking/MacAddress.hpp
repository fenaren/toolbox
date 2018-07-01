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
    explicit MacAddress(const std::string& mac_address_str);

    // Copy constructor
    explicit MacAddress(const MacAddress& mac_address);

    // Defines how to convert a MacAddress to a std::string
    operator std::string() const;

    // Destroys a MacAddress; does nothing, since this class doesn't dynamically
    // allocate memory.
    virtual ~MacAddress();

    // Reads a raw 6-byte MAC address from memory, "buf" is assumed to point to
    // a valid raw MAC address (NOT A C STRING!)
    void readRaw(const char* buf);

    // Writes a raw 6-byte MAC address to memory, "buf" is assumed to point to 6
    // bytes of properly allocated and available memory
    void writeRaw(char* buf) const;

    MacAddress& operator=(const std::string& mac_address_str);

    // MAC addresses are this many bytes long
    static const unsigned short MAC_LENGTH_BYTES = 6;

    // MAC address strings are this many characters long
    static const unsigned short MAC_MAX_STR_LENGTH_CHARS = 18;

private:

    // All constructors run this
    void initialize();
};

std::ostream& operator<<(std::ostream& os, const MacAddress& mac_address);

std::istream& operator>>(std::istream& is, MacAddress& mac_address);

bool operator==(const MacAddress&  mac_address1,
                const MacAddress&  mac_address2);
bool operator==(const MacAddress&  mac_address1,
                const std::string& mac_address2);
bool operator==(const std::string& mac_address1,
                const MacAddress&  mac_address2);

bool operator!=(const MacAddress&  mac_address1,
                const MacAddress&  mac_address2);
bool operator!=(const MacAddress&  mac_address1,
                const std::string& mac_address2);
bool operator!=(const std::string& mac_address1,
                const MacAddress&  mac_address2);

#endif
