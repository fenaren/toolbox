#if !defined RAW_DATA_FIELD_HPP
#define RAW_DATA_FIELD_HPP

#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

// Represents raw binary data.  Data is indexed in order of significance.
// Significance is assigned as if the raw data represented by this class were a
// single large integer.  Indexing can be done in order of increasing or
// decreasing significance.  Not much of importance is implemented here, see
// derived classes for more interesting stuff.
class RawDataField : public DataField
{
public:

    // Initializes arguments, does nothing else
    RawDataField(bool memory_internal, misc::DataIndexingMode indexing_mode);

    // Does nothing
    virtual ~RawDataField();

    // Indexing mode access
    misc::DataIndexingMode getIndexingMode() const;

    // Indexing mode mutator
    void setIndexingMode(misc::DataIndexingMode indexing_mode);

    // Memory internal accessor.  There is no corresponding mutator.
    bool getMemoryInternal() const;

protected:

    // Tosses a std::out_of_range exception if index >= size
    void throwIfIndexOutOfRange(unsigned long index, unsigned long size) const;

private:

    // Does this class own the memory at "byte_field_raw"?
    bool memory_internal;

    // Defaults for indexing modes for bits and bytes
    misc::DataIndexingMode indexing_mode;
};

//==============================================================================
inline misc::DataIndexingMode RawDataField::getIndexingMode() const
{
    return indexing_mode;
}

//==============================================================================
inline void RawDataField::setIndexingMode(misc::DataIndexingMode indexing_mode)
{
    this->indexing_mode = indexing_mode;
}

//==============================================================================
inline bool RawDataField::getMemoryInternal() const
{
    return memory_internal;
}


//==============================================================================
inline void RawDataField::throwIfIndexOutOfRange(unsigned long index,
                                                 unsigned long size) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
}

#endif
