# Smaut: Simple Mock asserts for Unit Tests

Smaut makes it easy to mock asserts in your unit test code to verify that
they are properly activating. It works with unmodified user code and even
object files. However, it does require a modified final link step and of
course needs asserts enabled.

Smaut works well with unit tests frameworks for c such as
[ccan tap](https://github.com/rustyrussell/ccan/blob/master/ccan/tap/_info)
and a [libtap](https://github.com/zorgnax/libtap).

## Example Code

**`do_division.h`**
```c
#ifndef DO_DIVISION_H
#define DO_DIVISION_H

unsigned int do_division(unsigned int a, unsigned int b);

#endif
```

**`do_division.c`**
```c
#include "do_division.h"
#include <assert.h>

unsigned int do_division(unsigned int a, unsigned int b)
{
    assert(b != 0);
    return a / b;
}
```

**`test_do_division.c`**
```c
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
```

The `assert_expect` call gives the expected assert failure when calling the
given function. If the assert is triggered as expected it is ignored and, the
function `assert_expect` function returns 1, otherwise it returns 0. If any
other assert is triggered, it is processed normally.

Note that the function will return directly from the location of the assert
call. In the above example, the division by zero will not occur and the
program will not abort. Any changes to global state will not be unwound and
must be handled by the caller.

## Available API

Various variants are available for matching a subset, or all of the available
assert parameters. Variants that intclude 2 or more parameters must match all
parameters.

* `int assert_expect_any(function call);`
* `int assert_expect(expression, function call);`
* `int assert_expect_with_func(expression, function name, function call);`
* `int assert_expect_with_file(expression, filename, function call);`
* `int assert_expect_func(function name, function call);`
* `int assert_expect_file(file name, function call);`
* `int assert_expect_file_with_func(filename, function name, function call);`
* `int assert_expect_all(expression, filename, function name, function call);`

Arguments:

* `function call`: The function call to make where an assert is expected,
including arguments.
* `expression`: The same expression given to the expected assertion.
* `function name`: The function name (without quotes) where the assertion
occurs.
* `filename`: The filename (given by `__FILE__`) where the assertion occurs.

## Build

smaut operates by intercepting the `__assert_fail` function. This wrapping is
currently implemented using the ld `--wrap` directive. This can be implemented
within CMake with the `target_link_options` command.

**`CMakeLists.txt`**
```cmake
cmake_minimum_required(VERSION 3.10)
project(smaut_example C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ccan)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

enable_testing()

add_executable(test_do_division
    test_do_division.c 
    do_division.c 
    ccan/ccan/tap/tap.c
    ../smaut.c
)

target_link_options(test_do_division PRIVATE LINKER:--wrap,__assert_fail)

add_test(NAME test_do_division COMMAND test_do_division)
```

## Credit/License

Crafted lovingly by humans. Licensed under the simplified BSD license (see the
LICENSE file). Copyright 2026, Russ Dill, `<russ.dill@gmail.com>`.
