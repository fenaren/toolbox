#if !defined TEST_HPP
#define TEST_HPP

#include <string>

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

    // Sets the name
    Test(const std::string& name);

    // Does nothing
    virtual ~Test();

    // Runs the test.  Runs body() while also executing code common to all
    // tests.  At the moment this is printing test status.
    Result run();

    // Name access and mutation
    void getName(std::string& name) const;
    void setName(const std::string& name);

protected:

    // Called by run().  Test is implemented here and the result is returned.
    virtual Result body() = 0;

private:

    // Textual test identifier
    std::string name;
};

inline void Test::getName(std::string& name) const
{
    name = this->name;
}

inline void Test::setName(const std::string& name)
{
    this->name = name;
}

#endif
