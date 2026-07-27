#include "../../headers/fsl.h"

typedef enum
{
	ANY_NULL 		= 0,
	ANY_INT 		= 1,
	ANY_CHAR 		= 2,
	ANY_FLOAT 		= 3,
	ANY_STRING 		= 4,
	ANY_ARRAY 		= 5,
	ANY_PTR_ARRAY 	= 6, // String, Array, Structs
	ANY_PTR 		= 7
} any_type;

typedef struct
{
	any_type type;
	any pointer;
} any_t;

const int ANY_META_SZ = sizeof(any_t);

ptr __get_any_meta__(any p)
{ return (any_t *)((char *)p - ANY_META_SZ); }

any any_allocate(len_t sz, i32 len)
{
	i32 num = sz ? sz * len : len;
	if(len == 0)
		return NULL;

	num += ANY_META_SZ;
	any_t *p = allocate(0, num);
	if(!p)
		return NULL;

	p->type = ANY_NULL;
	p->pointer = (any)(p + ANY_META_SZ);

	return p->pointer;
}

any convert_to_type(any p, any_type type)
{
	any_t *m = __get_any_meta__(p);
	switch(m->type)
	{
		case ANY_INT:
			int n = !(*(int *)m->pointer) ? 0 : (*(int *)m->pointer) + '0';
			return to_heap(&n, sizeof(int));
		case ANY_CHAR:
			return to_heap(&((string)m->pointer)[0], sizeof(int));
		case ANY_PTR:
			return (ptr)m->pointer;
	}
}

/* 
	[NOTE] Convert v to p type and compare

string STRING_PTR = "3";

if(!any_cmp(STRING_PTR, 3, 4))
	fsl_panic("mismatch");

*/
int any_cmp(any p, any v, any_type type, i32 len)
{
	if(*(int *)((char *)p - ANY_META_SZ - sizeof(int)) == 0x7C)
	{
		fsl_panic("invalid memory provided...!\n");
	}

	any_t *n = (any_t *)((char *)p - ANY_META_SZ);
}
