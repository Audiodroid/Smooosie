
#include "catch2/catch_all.hpp"
#include "trompeloeil.hpp"

using namespace trompeloeil;

class MyClassBase
{
    virtual int myFunc() = 0;
};

class MyClass : MyClassBase
{
public:
    int myFunc() override
    {
        return 1;
    }
};

class MyClassMock : MyClassBase
{
    MAKE_MOCK0 (myFunc, int(), override);
};

TEST_CASE ("Testing a mock", "Mock")
{
    auto myClass = MyClass();
    auto x = myClass.myFunc();

    auto myClassMock = MyClassMock();
    ALLOW_CALL (myClassMock, myFunc()).RETURN (2);
    auto y = myClassMock.myFunc();

    REQUIRE (x != y);
}
