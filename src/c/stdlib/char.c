#include "../../../headers/fsl.h"

public i32 is_ascii(char c)
{ return (unsigned char)c <= 127; }

public i32 is_lowercase(char c)
{ return (c >= 'a' && c <= 'z'); }

public i32 is_uppercase(char c)
{ return (c >= 'A' && c <= 'Z'); }

public i32 is_ascii_alpha(char c)
{
	unsigned char b = (unsigned char)c;
	return (b >= 'a' && b <= 'z' || b >= 'A' && b <= 'Z');
}

public i32 is_ascii_digit(char c)
{
	unsigned char b = (unsigned char)c;
	return (b >= '0' && b <= '9');
}