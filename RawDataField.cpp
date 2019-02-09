#include <cstring>
#include <new>
#include <stdexcept>

#include "RawDataField.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
RawDataField::RawDataField(bool                   memory_internal,
                           misc::DataIndexingMode indexing_mode) :
    DataField(),
    memory_internal(memory_internal),
    indexing_mode(indexing_mode)
{
}

//==============================================================================
RawDataField::~RawDataField()
{
}
