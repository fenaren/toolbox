#if !defined PULL_UPDATE_PUSH_HPP
#define PULL_UPDATE_PUSH_HPP

//==============================================================================
// Does a couple things for hard-to-understand reasons.
//
// First we pull what we pull a T out of the memory starting at raw_dptest +
// offset (this function is used multiple times in succession and, as can be
// seen on the last line, offset is bumped each time, meaning a new section of
// memory is read each time).  Because we should have written this memory in the
// byte ordering that is opposite of this host system, this T has to be
// byteswapped again to be sensical.  This value is then left alone to be
// returned in the "dptest_var" argument.
//
// Second, we save a copy of an incremented "dptest_var" into
// "dptest_var_updated".  This value is then written byteswapped into the same
// memory location we read as described in the paragraph above, meaning the
// memory location is now incremented but otherwise unchanged.  Later, readRaw()
// will read this, and we can test for presence of the incremented value.
//
// Lastly, offset is bumped past the memory location we read with it to prepare
// for its next usage.
//==============================================================================
template <class T>
void pullUpdatePush(unsigned char* raw_dptest,
                    T&             dptest_var,
                    T&             dptest_var_updated,
                    unsigned int&  offset,
                    bool           swap);

#endif
