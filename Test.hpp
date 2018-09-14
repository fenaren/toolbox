#if !defined TEST_HPP
#define TEST_HPP

class Test
{
public:

    // Executed tests report one of these
    enum Result
    {
        PASSED  = 0,
        FAILED  = 1,
        SKIPPED = 2
    };

    Test();

    virtual ~Test();

    // Derived classes should override this to implement the desired test
    virtual Result run() = 0;
};

#endif
