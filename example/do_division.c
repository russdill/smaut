#include "do_division.h"
#include <assert.h>

unsigned int do_division(unsigned int a, unsigned int b)
{
    assert(b != 0);
    return a / b;
}
