#include <stdint.h>
#include <assert.h>

unsigned int nondet_uint();
void __CPROVER_assume(int x);
void __CPROVER_assert(int x, char y[]);

// macros
#define assert2(x, y) __CPROVER_assert(x, y)
#define assume(x) __CPROVER_assume(x)
