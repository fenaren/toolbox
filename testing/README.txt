All tests (directly or indirectly) derive from the "Test" class.  The Test class
captures generic test behavior at the highest level.  See the Test class header
for more information on the Test class.

The "TestCases" class allows sets of related Tests to be grouped and executed
together.  This occurs when implementing class-level unit tests, since these
tests are naturally related.  See the TestCases header for more information on
the TestCases class.

TestCases is a Test; the TestCases class derives from the Test class.  This
allows instances of the TestCases class to group standard Test objects as well
as other TestCases objects.  This allows the construction of a tree of related
tests, where all the internal nodes are TestCases and the leaves are standard
Tests.

Standard form for simple class-level unit tests is to use a single
implementation file named "Widget_test.cpp", where "Widget" is the name of the
class under test (CUT).  As one way of easing the pain of writing tests, all
unit tests for the CUT are defined in this single file.  Separate header files
are foregone in favor of the macros defined in "TestMacros.hpp", which are used
to define what would normally be header file content at the beginning of the
implementation file.

Content in a standard class-level unit test implementation file is ordered as
follows.

1. All needed include files.

2. The TEST_CASES_PROGRAM_BEGIN macro.  This macro begins the declaration of a
   TestCases that is used to group all the unit tests in the implementation
   file.

3. One or more TEST macros.  These macros declare Tests for each unit test.

4. The TEST_CASES_PROGRAM_END macro.  This ends the TestCases declaration begun
   earlier with TEST_CASES_PROGRAM_BEGIN.  It also writes a main() function that
   will create and run the TestCases in a standard way.

5. Declarations for any constant data or functions used by multiple unit tests.
   BE CAREFUL NOT TO INTRODUCE DEPENDENCIES BETWEEN UNIT TESTS HERE.

6. Definition of the addTestCases() pure virtual member function of the
   TestCases class.

7. Definitions of all unit tests.  These are implementations of the pure virtual
   body() class member function within each of the tests declared using the TEST
   macro.

8. Definitions of any functions declared in number 5 above.

The implementation file, along with all other content related to the test
(necessary CMake files, reference data, notes, etc.) goes in a subdirectory
named "Widget_test".  This subdirectory is located in the same directory as the
CUT.  See the template class test "TemplateClass_test" at the top level of this
repository for examples of the structure of class-level unit tests and the usage
of the test macros.
