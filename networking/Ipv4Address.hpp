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
    explicit Ipv4Address(const std::string& ipv4_address_str);

    // Copy constructor
    explicit Ipv4Address(const Ipv4Address& ipv4_address);

    // Defines how to convert a MacAddress to a std::string
    operator std::string() const;

    // Destroys a Ipv4Address; does nothing, since this class doesn't
    // dynamically allocate memory.
    virtual ~Ipv4Address();

    // Reads a raw 4-byte IPv4 address from memory, "buf" is assumed to point to
    // a valid IPv4 address
    void readRaw(const char* buf);

    // Writes a raw 4-byte IPv4 address to memory, "buf" is assumed to point to
    // 4 bytes of properly allocated and available memory
    void writeRaw(char* buf) const;

    Ipv4Address& operator=(const std::string& ipv4_address_str);

    // IPv4 addresses are this many bytes long
    static const unsigned short IPV4_LENGTH_BYTES = 4;

    // IPv4 address strings are this many characters long
    static const unsigned short IPV4_MAX_STR_LENGTH_CHARS = 16;

private:

    // All constructors run this
    void initialize();
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
