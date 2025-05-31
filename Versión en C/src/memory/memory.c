#include "memory.h"

void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}
