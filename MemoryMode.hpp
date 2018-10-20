#if !defined MEMORY_MODE_HPP
#define MEMORY_MODE_HPP

// This is used by constructs which can store relevant data internally or
// externally, depending on how they are configured or used.  For example, a
// class may be programmed to perform a relatively expensive memory allocation
// internally, or optionally not perform that allocation and use pre-allocated
// memory that has been prepared by some other means.

// This concept seems like it could be implemented as a simple abstract class
// (an "interface"), but doesn't seem worth the trouble.

enum MemoryMode
{
    MEMORY_INTERNAL,
    MEMORY_EXTERNAL
};

#endif
