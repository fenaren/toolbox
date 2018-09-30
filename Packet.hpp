#if !defined PACKET_HPP
#define PACKET_HPP

#include <string>
#include <vector>

#include "Field.hpp"

class Packet : public Field
{
public:

    // Sets packet name
    explicit Packet(const std::string& name = "");

    // Does nothing
    virtual ~Packet();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

protected:

    virtual void addField(Field* field);

private:

    std::vector<Field*> fields;
};

inline void Packet::addField(Field* field)
{
    fields.push_back(field);
}

#endif
