#include "lib/memory.h"
#include "lib/types.h"

void *memcpy(void *restrict dest, const void *restrict src, int n)
{
    ubyte_t *pdest = dest;
    const ubyte_t *psrc = src;

    for (int i = 0; i < n; i++)
        pdest[i] = psrc[i];

    return dest;
}

void *memset(void *s, int c, int n)
{
    ubyte_t *p = s;

    for (int i = 0; i < n; i++)
        p[i] = (ubyte_t)c;

    return s;
}

void *memmove(void *dest, const void *src, int n)
{
    ubyte_t *pdest = dest;
    const ubyte_t *psrc = src;

    if ((int)src > (int)dest) {
        for (int i = 0; i < n; i++)
            pdest[i] = psrc[i];
    } else if ((int)src < (int)dest) {
        for (int i = n; i-- > 0; )
            pdest[i] = psrc[i];
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, int n)
{
    const ubyte_t *p1 = s1;
    const ubyte_t *p2 = s2;

    for (int i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return p1[i] < p2[i] ? -1 : 1;
    }

    return 0;
}
