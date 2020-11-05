#include <setjmp.h>
#include <stdint.h>
#include "buf.h"

int aborted;
static jmp_buf escape;
int* buffer = 0;

#suite Buffer
#test init_capacity
	ck_assert_int_eq(buf_capacity(buffer), 0);
	ck_assert_int_eq(buf_size(buffer), 0);
	buf_push(buffer, 5);
	ck_assert_int_eq(buf_size(buffer), 1);
	ck_assert(buffer[0] == 5);
	buf_clear(buffer);
	ck_assert_int_eq(buf_size(buffer), 0);
	ck_assert_ptr_ne(buffer, 0);
	buf_free(buffer);
	ck_assert_ptr_eq(buffer, 0);

#test clear_null
	buf_clear(buffer);
	ck_assert_int_eq(buf_size(buffer), 0);
	ck_assert_ptr_eq(buffer, 0);

#test push_index_select
	long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
	ck_assert_int_eq(buf_size(ai), 10000);
	int match = 0;
	for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
	ck_assert_int_eq(match, 10000);
	buf_free(ai);

#test grow_trunk
	long *ai = 0;
	buf_grow(ai, 1000);
	ck_assert_int_eq(buf_capacity(ai), 1000);
	ck_assert_int_eq(buf_size(ai), 0);
    buf_trunc(ai, 100);
	ck_assert_int_eq(buf_capacity(ai), 100);
    buf_free(ai);

#test pop
	buf_push(buffer, 1);
    buf_push(buffer, 2);
    buf_push(buffer, 3);
    buf_push(buffer, 4);
	ck_assert_int_eq(buf_size(buffer), 4);
    ck_assert_int_eq(buf_pop(buffer), 4);
    buf_trunc(buffer, 3);
	ck_assert_int_eq(buf_size(buffer), 3);
    ck_assert_int_eq(buf_pop(buffer), 3);
    ck_assert_int_eq(buf_pop(buffer), 2);
    ck_assert_int_eq(buf_pop(buffer), 1);
	ck_assert_int_eq(buf_size(buffer), 0);
    buf_free(buffer);	

