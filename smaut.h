/*
 * Smaut: Simple Mock asserts for Unit Tests
 * Copyright 2026 Russ Dill <russ.dill@gmail.com>
 */
#ifndef _MOCK_ASSERT_H
#define _MOCK_ASSERT_H

#include <setjmp.h>
#include <stddef.h>

#define _assert_expect(a, f, l, fn, func) ({	\
	int __ret;				\
	jmp_buf __jmp;				\
	__assert_expect(a, f, l, fn, &__jmp);	\
	__ret = setjmp(__jmp);			\
	if (!__ret)				\
		func;				\
	__ret;					\
})

#define assert_expect_any(expr, func) \
	_assert_expect(NULL, NULL, 0, NULL, func)

#define assert_expect(expr, func) \
	_assert_expect(#expr, NULL, 0, NULL, func)

#define assert_expect_with_func(expr, fn, func) \
	_assert_expect(#expr, NULL, 0, #fn, func)

#define assert_expect_with_file(expr, f, func) \
	_assert_expect(#expr, #f, 0, NULL, func)

#define assert_expect_func(fn, func) \
	_assert_expect(NULL, NULL, 0, #fn, func)

#define assert_expect_file(f, func) \
	_assert_expect(NULL, #f, 0, NULL, func)

#define assert_expect_file_with_func(f, fn, func) \
	_assert_expect(NULL, #f, 0, #fn, func)

#define assert_expect_all(expr, f, fn, func) \
	_assert_expect(#expr, #f, 0, #fn, func)

void __assert_expect(const char *assertion, const char *file,
                unsigned int line, const char *function, jmp_buf *jmp);

#endif
