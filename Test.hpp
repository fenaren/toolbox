#if !defined TEST_HPP
#define TEST_HPP

class Test
{
public:

    // Executed tests report one of these
    enum Result
    {
        PASSED,
        FAILED,
        SKIPPED
    };

    // Neither of these do anything
    Test();
    virtual ~Test();

    // Derived classes should override this to implement the desired test
    virtual Result run() = 0;
};

#endif
