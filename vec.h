#ifndef __VEC_H__
#define __VEC_H__

#include <string.h>
#include "utils.h"

static void vec_expand(char **data, int *length, int *capacity, int memsz) {
	if (*length + 1 > *capacity) {
		if (*capacity == 0) {
			*capacity = 1;
		} else {
			*capacity <<= 1;
		}
		*data = Realloc(*data, *capacity * memsz);
	}
}

static void vec_splice(
  char **data, int *length, int *capacity, int memsz, int start, int count
) {
	(void) capacity;
	memmove(*data + start * memsz,
	      *data + (start + count) * memsz,
	      (*length - start - count) * memsz);
}


#define Vec(T)\
  struct { T *data; int length, capacity; }


#define vec_unpack(v)\
  (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)


#define vec_init(v)\
 	memset((v), 0, sizeof(*(v)))


#define vec_deinit(v)\
	Free((v)->data)


#define vec_clear(v)\
	((v)->length = 0)


#define vec_push(v, val)\
	( vec_expand(vec_unpack(v)),\
		(v)->data[(v)->length++] = (val) )


#define vec_splice(v, start, count)\
	( vec_splice(vec_unpack(v), start, count),\
		(v)->length -= (count) )

#endif
