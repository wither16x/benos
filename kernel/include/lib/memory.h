#ifndef LIB_MEMORY_H_
#define LIB_MEMORY_H_

void *memcpy(void *restrict dest, const void *restrict src, int n);
void *memset(void *s, int c, int n);
void *memmove(void *dest, const void *src, int n);
int memcmp(const void *s1, const void *s2, int n);

#endif /* LIB_MEMORY_H_ */
