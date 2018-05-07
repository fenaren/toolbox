#if !defined DATA_HPP
#define DATA_HPP

#include <cstring>
#include <vector>

// Represents an amount of data.
class Data
{
public:

    Data();

    Data(unsigned int reserve);

    Data(char* data, unsigned int length);

    // Does nothing
    ~Data();

    void set(char* data, unsigned int length);

    void get(char*& data, unsigned int& length) const;

    unsigned int getLength() const;

    // Allows the use of brackets to index into the MAC address
    char& operator[](const unsigned int index);

    bool operator==(const Data& data) const;

    bool operator!=(const Data& data) const;

private:

    std::vector<char> data;
};

inline void Data::set(char* data, unsigned int length)
{
    memcpy(this->data.data(), data, length);
}

inline void Data::get(char*& data, unsigned int& length) const
{
    memcpy(data, this->data.data(), length);
}

inline unsigned int Data::getLength() const
{
    return data.size();
}

#endif
