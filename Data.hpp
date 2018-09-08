#if !defined DATA_HPP
#define DATA_HPP

class Data
{
public:

    // Stores length internally, that's it
    Data(unsigned int length);

    // Does nothing
    virtual ~Data();

    // Reads and internalizes raw data from memory
    virtual void read(const unsigned char* buffer) = 0;

    // Writes raw data to memory based on internal state
    virtual void write(unsigned char* buffer) const = 0;

    unsigned int getLength() const;

private:

    unsigned int length;
};

inline unsigned int Data::getLength() const
{
    return length;
}

#endif
