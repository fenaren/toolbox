#if !defined DATA_HPP
#define DATA_HPP

// Represents an amount of data.
class Data
{
public:

    Data();

    Data(char* data, unsigned int length);

    // Does nothing
    ~Data();

    void set(char* data, unsigned int length);

    void setData(char* data);

    void setLength(unsigned int length);

    void get(char*& data, unsigned int& length) const;

    char* getData() const;

    unsigned int getLength() const;

    bool operator==(const Data& data) const;

    bool operator!=(const Data& data) const;

private:

    char* data;

    unsigned int length;
};

inline void Data::set(char* data, unsigned int length)
{
    this->data   = data;
    this->length = length;
}

inline void Data::setData(char* data)
{
    this->data = data;
}

inline void Data::setLength(unsigned int length)
{
    this->length = length;
}

inline void Data::get(char*& data, unsigned int& length) const
{
    data   = this->data;
    length = this->length;
}

inline char* Data::getData() const
{
    return data;
}

inline unsigned int Data::getLength() const
{
    return length;
}

#endif
