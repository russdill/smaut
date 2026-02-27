/*
 * Smaut: Simple Mock asserts for Unit Tests
 * Copyright 2026 Russ Dill <russ.dill@gmail.com>
 */
#include <assert.h>
#include <string.h>

#include "smaut.h"

static __thread const char *__mock_assertion;
static __thread const char *__mock_file;
static __thread unsigned int __mock_line;
static __thread const char *__mock_function;

static __thread jmp_buf *__mock_jmp;
static __thread int __mock_expect;

extern void __real___assert_fail (const char *__assertion, const char *__file,
	unsigned int __line, const char *__function)
	__THROW __attribute__ ((__noreturn__)) __COLD;

void __wrap___assert_fail (const char *__assertion, const char *__file,
	unsigned int __line, const char *__function)
	__attribute__ ((__noreturn__));

void __wrap___assert_fail (const char *__assertion, const char *__file,
	unsigned int __line, const char *__function)
{
	if (!__mock_expect ||
			(__mock_assertion && strcmp(__mock_assertion, __assertion)) ||
			(__mock_file && strcmp(__mock_file, __file)) ||
	   		(__mock_line && __mock_line != __line) ||
			(__mock_function && strcmp(__mock_function, __function)))
		__real___assert_fail(__assertion, __file, __line, __function);
	__mock_expect = 0;
	longjmp(*__mock_jmp, 1);
}

void __assert_expect(const char *assertion, const char *file, 
		unsigned int line, const char *function, jmp_buf *jmp)
{
	__mock_assertion = assertion;
	__mock_file = file;
	__mock_line = line;
	__mock_function = function;
	__mock_expect = 1;
	__mock_jmp = jmp;
}
