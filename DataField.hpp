#if !defined DATA_FIELD_HPP
#define DATA_FIELD_HPP

class DataField
{
public:

    // Neither of these do anything
    DataField();
    virtual ~DataField();

    // Reads the data field from the "buffer" memory location.
    virtual unsigned int readRaw(const unsigned char* buffer) = 0;

    // Writes the data field to the "buffer" memory location.
    virtual unsigned int writeRaw(unsigned char* buffer) const = 0;

    // Returns the size of this data field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const = 0;
};

#endif
