#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

void* memmove(void* dst, const void* src, size_t len);
void* memcpy(void* dst, const void* src, size_t len);
void* memset(void* dst, int b, size_t len);

#endif
