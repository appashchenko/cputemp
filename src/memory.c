#include "../include/memory.h"

void* memmove(void* dst, const void* src, size_t len) {
  ssize_t pos = (dst <= src) ? -1 : (long)len;
  void* ret = dst;

  while (len--) {
    pos += (dst <= src) ? 1 : -1;
    ((char*)dst)[pos] = ((char*)src)[pos];
  }
  return ret;
}

void* memcpy(void* dst, const void* src, size_t len) {
  return memmove(dst, src, len);
}

void* memset(void* s, int c, size_t count) {
  char* xs = (char*)s;

  while (count--)
    *xs++ = (char)c;
  return s;
}
