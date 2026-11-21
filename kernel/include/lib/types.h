#ifndef LIB_TYPES_H_
#define LIB_TYPES_H_

/*
 * Sizes of types in OpenWatcom V2:
 *
 * - char is 1 byte
 * - short and int are 2 bytes
 * - long is 4 bytes
 * - long long is 8 bytes
 */

typedef char        sbyte_t;
typedef short       sword_t;
typedef long        sdword_t;
typedef long long   sqword_t;

typedef unsigned char       ubyte_t;
typedef unsigned short      uword_t;
typedef unsigned long       udword_t;
typedef unsigned long long  uqword_t;

typedef _Bool bool_t;
#define TRUE ((bool_t)1)
#define FALSE ((bool_t)0)

#endif /* LIB_TYPES_H_ */
