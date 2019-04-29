#if !defined TEST_HPP
#define TEST_HPP

#include <string>

// All tests derive from the "Test" class.  The Test class captures generic test
// behavior such as defining the standard way in which all tests are executed.
// The Test class is intended to represent tests of any level (unit,
// integration, system, etc.) and complexity.

// Meaningful test content specific to each test is defined by the user using
// the pure virtual body() member function.  Tests are run using the run()
// member function (this calls the body() function and also runs some other
// generic test content).  Status of the test is returned by the run function
// using the Result enumeration.

// Tests must have a name.  The name is used only to help a human observer
// identify output related to each test.

// Consider using the TEST macro (defined in TestMacros.hpp) to declare a
// derived class to use to implement meaningful tests.  See also README.txt in
// the top-level "testing" directory for a general description of how tests are
// structured.
class Test
{
public:

    // The run() member function uses this to report test status
    enum Result
    {
        PASSED, // Test passed successfully
        FAILED, // Test did not pass successfully
        SKIPPED // Test did not meaningfully execute
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

//==============================================================================
inline void Test::getName(std::string& name) const
{
    name = this->name;
}

//==============================================================================
inline void Test::setName(const std::string& name)
{
    this->name = name;
}

#endif
