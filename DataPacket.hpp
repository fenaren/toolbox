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

protected:

    virtual void addDataField(DataField* data_field);

private:

    std::vector<DataField*> data_fields;
};

inline void DataPacket::addDataField(DataField* data_field)
{
    data_fields.push_back(data_field);
}

#endif
