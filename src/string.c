#include "../include/string.h"

size_t strlen(const char* s) {
  const char* sc;

  for (sc = s; *sc != '\0'; ++sc)
  ;

  return (size_t)(sc - s);
}

int atoi(const char* s) {
  int ret = 0;
  unsigned int d;
  int neg = 0;

  if (*s == '-') {
    neg = 1;
    s++;
  }

  while (1) {
    d = (*s++) - '0';
    if (d > 9) break;
    ret *= 10;
    ret += d;
  }

  return neg ? -ret : ret;
}

const char* ltoa(int in) {
  /* large enough for -9223372036854775808 */
  static char buffer[21];
  char* pos = buffer + sizeof(buffer) - 1;
  int neg = in < 0;
  unsigned int n = neg ? -in : in;

  *pos-- = '\0';
  do {
    *pos-- = '0' + n % 10;
    n /= 10;
    if (pos < buffer) return pos + 1;
  } while (n);

  if (neg) *pos-- = '-';
  return pos + 1;
}
