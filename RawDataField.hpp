#if !defined RAW_DATA_FIELD_HPP
#define RAW_DATA_FIELD_HPP

#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class RawDataField : public DataField
{
public:

    RawDataField(bool memory_internal, misc::DataIndexingMode indexing_mode);
    virtual ~RawDataField();

    misc::DataIndexingMode getIndexingMode() const;
    void setIndexingMode(misc::DataIndexingMode indexing_mode);

    bool getMemoryInternal() const;

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

#endif
