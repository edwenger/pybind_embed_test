#include <assert.h>

void testOne()
{
    assert(1 + 2 != 5);
}

void testTwo()
{
    assert(1 + 1 == 2);
}

int main(int, char**)
{
    testOne();
    testTwo();
}
