#if !defined DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <string>
#include <vector>

#include "DataField.hpp"

class DataPacket : public DataField
{
public:

    // Sets packet name
    explicit DataPacket(const std::string& name = "");

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

    std::vector<DataField*> data_fields;

    unsigned int byte_alignment;
};

inline void DataPacket::registerDataField(DataField* data_field)
{
    data_fields.push_back(data_field);
}

inline void DataPacket::setByteAlignment(unsigned int byte_alignment)
{
    this->byte_alignment = byte_alignment;
}

inline unsigned int DataPacket::getByteAlignment() const
{
    return byte_alignment;
}

#endif
