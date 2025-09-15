#define ARR_H
#include "../../headers/stdlib/init.h"

int arr_contains(arr args, str *needle)
{
	if(!args || !needle)
        return -1;

    for(int i = 0; ((char *)args)[i] != NULL; i++)
        if((char *)((char **)args)[i] == ((char *)needle))
            return i;

    return -1;
}
