#if !defined DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "DataField.hpp"

class DataPacket : public DataField
{
public:

    // Sets packet name
    explicit DataPacket(const std::string& name);

    // Does nothing
    virtual ~DataPacket();

    // Reads the field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Writes the field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    // Byte alignment mutator
    void setByteAlignment(unsigned int byte_alignment);

    // Byte alignment access
    unsigned int getByteAlignment() const;

protected:

    virtual void registerDataField(DataField* data_field);

private:

    // Computes amount of padding needed after a field given the current byte
    // alignment setting
    unsigned int computePadding(unsigned int field_length) const;

    // All contained data fields, indexed by order (IBO)
    std::vector<DataField*> data_fields_ibo;

    // All contained data fields, indexed by name (IBN)
    std::map<std::string, DataField*> data_fields_ibn;

    unsigned int byte_alignment;
};

inline void DataPacket::setByteAlignment(unsigned int byte_alignment)
{
    if (byte_alignment == 0)
    {
        throw std::invalid_argument(
            "Nonsensical byte alignment value of 0 specified (must be 1 or "
            "greater)");
    }

    this->byte_alignment = byte_alignment;
}

inline unsigned int DataPacket::getByteAlignment() const
{
    return byte_alignment;
}

#endif
