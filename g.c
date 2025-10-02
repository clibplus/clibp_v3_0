#include <stdio.h>
#include <string.h>

#define foreach(arr, element_callback, op) \
	do { \
		for(int i = 0; arr[i] != NULL; i++) { \
			void *element_callback = arr[i]; \
			op; \
		} \
	} while(0)

int main() {
	char *TEST[10] = {"LOL", "GAY", "FAG", "SKID", NULL};
	foreach(TEST, gay,
		if(!strcmp(gay, "FAG"))
			printf("[%d]: %s\n", i, (char *)gay);
	);
	return 0;
}
