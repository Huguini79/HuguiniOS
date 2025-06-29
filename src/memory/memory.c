#include "memory.h"

void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

int memcmp(void* s1, void* s2, int count) {
	char* c1 = s1;
	char* c2 = s2;
	while(count-- > 0) {
		if(*c1++ != *c2++) {
			return c1[-1] < c2[-1] ? -1: 1;
		}
	}
	
	return 0;
	
}
