#ifndef _UTIL_H
#define _UTIL_H

#include "postgres.h"

char *to_cptr(text *);
unsigned long text_len(text *);

#define min(a, b) ( (a) < (b) ? (a) : (b) )
#define min3(a, b, c) min(min(a, b), c)
#define min4(a, b, c, d) min(min3(a, b, c), d)

#define BITSET(name, x) unsigned int name[((x) >> 5) + !!((x) & 31)] = {0}
#define SET(name, x) name[(x) >> 5] |= (unsigned int)(1U << ((x) & 31))
#define CLEAR(name, x) name[(x) >> 5] &= (unsigned int)(~0U ^ (1U << ((x) & 31)))
#define CHECK(name, x) !!(name[(x) >> 5] & (1U << ((x) & 31)))
#define RESET(name) memset(name, 0, sizeof(name))

#endif /* _UTIL_H */
