#define STR_H
#include "../../headers/stdlib/init.h"

//str create_string(int sz, int len) {
//
//}

len_t str_len(str buffer)
{
	if(!buffer)
		return 0;

	len_t count = 0;
	for(len_t i = 0; buffer[i] != '\0'; i++)
		count++;

	return count;
}

// String Compare
bool str_cmp(const str src, const str needle)
{
	if(!src || !needle)
		return false;

	len_t len = str_len(src);
	len_t len2 = str_len(needle);

	if(len2 > len)
		return false;

	for(int i = 0; i < len2; i++)
	{
		if(src[i] != needle[i])
			return false;
	}

	return true;
}

// String Append
int stra(str buff, const str sub) {
	if(!buff || !sub)
		return 0;

	len_t src_len = str_len(buff);
	len_t len = str_len(sub);
	for(int i = src_len, c = 0; i < len; i++, c++) {
		buff[i] = sub[c];
	}

	return 1;
}

// Find Char (to find multiple, increament match each call until -1)
pos_t find_char(const str buff, const char ch, int match)
{
	if(!buff || ch == 0)
		return -1;

	len_t len = str_len(buff);
	for(int i = 0; i < len; i++)
	{
		if(buff[i] == '\0')
			break;

		if(buff[i] == ch && i == match)
			return i;
	}

	return -1;
}

// Find String (to find multiple, increament match each call until -1)
pos_t find_str(const str buff, const str needle)
{
	if(!buff || !needle)
		return -1;

	len_t len = str_len(buff);
	len_t needle_len = str_len(needle);
	for(int i = 0; i < len; i++)
	{
		if(buff[i] == '\0')
			break;

		for(int c = 0; c < needle_len; c++)
		{
			if(buff[i + c] != needle[c])
				break;

			if(c == (needle_len - 1) && buff[i + c] == needle[c])
				return i;
		}
	}

	return -1;
}
