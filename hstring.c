#include <fsl.h>

typedef i8 *string_t;

#define __STRING_METADATA_SZ__ sizeof(i64)

i64 get_string_size(string_t buffer)
{ return *(i64 *)(buffer - __STRING_METADATA_SZ__ - 1); }

i64 get_original_string_pointer(string_t buffer)
{ return *(i64 *)(buffer - __STRING_METADATA_SZ__ - 1); }

string_t init_string(int len)
{
	string_t p = allocate(0, __STRING_METADATA_SZ__ + len + 2);
	*((i64 *)p) = len;

	return p + __STRING_METADATA_SZ__ + 1;
}

string_t create_string(string q)
{
	i64 len = _str_len(q);
	string_t p = (i8 *)allocate(0, __STRING_METADATA_SZ__ + len + 2);
	*((i64 *)p) = len;

	mem_cpy(p + __STRING_METADATA_SZ__ + 1, q, len);
	return p + __STRING_METADATA_SZ__ + 1;
}

public bool string_append(string_t *buffer, string sub)
{
	if(!buffer || !sub)
		return false;
	
	string_t original_p = get_original_string_pointer(*buffer);
	i64 len = *(i64 *)original_p;
	i64 slen = str_len(sub);

	i64 new_len = len + slen;
	string_t new_p = to_heap(original_p, new_len + __STRING_METADATA_SZ__ + 1);
	*((i64 *)new_p) = new_len;

	*buffer = new_p + __STRING_METADATA_SZ__ + 1;

	mem_cpy((*buffer) + len, sub, slen);
	return true;
}

public bool string_replace(string_t *buffer, string find, string replacement)
{
	if(!buffer || !find)
		return false;

	string_t original_p = get_original_string_pointer(*buffer);
	i64 len = *(i64 *)original_p;
	i64 slen = str_len(find);
	i64 vlen = str_len(replacement);

	if(slen <= vlen)
	{
		for(int i = 0, idx = 0; i < len; i++)
		{
			if(mem_cmp((*buffer) + i, find, slen))
			{
				for(int c = 0; c < vlen; c++)
					(*buffer)[idx++] = replacement[c];

				continue;
			}

			(*buffer)[idx++] = (*buffer)[i];
		}
		
		return true;
	} else {
		int new_len = len + vlen - (vlen - slen);
		string_t new_buff = to_heap(original_p, new_len + sizeof(i64) + 1);

		for(int i = 0, idx = 0; i < len; i++)
		{
			if(mem_cmp((*buffer) + i, find, slen))
			{
				for(int c = 0; c < vlen; c++)
					new_buff[idx++] = replacement[c];

				i += vlen;
				continue;
			}

			new_buff[idx++] = (*buffer)[i];
			new_buff[idx] = '\0';
		}

		*buffer = new_buff + sizeof(i64) + 1;
		return true;
	}

	return false;
}

int entry()
{
	toggle_debug_mode();
	printi(sizeof(__meta__));
	string_t n = create_string("Skid");
	println(n);

	string v = allocate(0, 6);
	mem_cpy(v, " dick", 5);

	if(!string_append(&n, " fag") || !string_append(&n, v))
		fsl_warning("failed to append to string");
	
	string_replace(&n, "fag", "skid");
	int sz = get_string_size(n);
	int len = _str_len(n);
	print("Size: "), printi(sz), print(" '"), print_sz(n, sz), println("'");
	print("Actual Size: "), printi(len), print(" '"), print_sz(n, sz), println("'");
	print("Heap Used: "), printi(used_mem), print("/"), printi(_HEAP_PAGE_), println(NULL);
	return 0;
}
