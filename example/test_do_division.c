#include "smaut.h"
#include "do_division.h"

#include <stdlib.h>

#include <ccan/tap/tap.h>

int main(void)
{
    plan_tests(2);

    ok1(do_division(8, 2) == 4);
    ok1(assert_expect(b != 0, do_division(8, 0)));

    exit(exit_status());
}
