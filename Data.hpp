#if !defined DATA_HPP
#define DATA_HPP

class Data
{
public:

    // Does nothing
    Data(unsigned int length_bytes, unsigned int max_string_length_chars);

    // Does nothing
    virtual ~Data();

    // Overridden by derived classes to read and internalize raw data from
    // memory as appropriate for the derived type
    virtual void read(unsigned char* buf) = 0;

    // Overridden by derived classes to write raw data (based on class state) to
    // memory
    virtual void write(unsigned char* buf) const = 0;

    unsigned int getLengthBytes() const;

    unsigned int getMaxStringLengthChars() const;

private:

    unsigned int length_bytes;
    unsigned int max_string_length_chars;
};

inline unsigned int Data::getLengthBytes() const
{
    return length_bytes;
}

inline unsigned int Data::getMaxStringLengthChars() const
{
    return max_string_length_chars;
}

#endif
