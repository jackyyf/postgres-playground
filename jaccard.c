#include "postgres.h"
#include "fmgr.h"
#include "util.h"

#define HASH2(a, b) ((unsigned long)(a) << 8 | (unsigned long)(b))

PG_FUNCTION_INFO_V1(jaccard_index);

Datum jaccard_index(PG_FUNCTION_ARGS) {
	static BITSET(bset1, 65536);
	static BITSET(bset2, 65536);
	text *str1 = (text *)PG_GETARG_TEXT_P(0);
	text *str2 = (text *)PG_GETARG_TEXT_P(1);
	unsigned long l1 = text_len(str1), l2 = text_len(str2);
	unsigned long i, hash;
	unsigned long ci = 0, c2 = 0;
	unsigned long *h1 = (unsigned long *)palloc(sizeof(unsigned long) * (l1 + 1)), *h1tail = h1, *it;
	RESET(bset1); RESET(bset2);
	if (l1 == 0 || l2 == 0) {
		PG_RETURN_FLOAT8((float8).0);
	}
	SET(bset1, HASH2('\0', VARDATA(str1)[0]));
	*h1 = HASH2('\0', VARDATA(str1)[0]); ++ h1tail;
	SET(bset2, HASH2('\0', VARDATA(str2)[0]));
	c2 = 1;
	for(i = 1; i < l1; ++ i) {
		hash = HASH2(VARDATA(str1)[i - 1], VARDATA(str1)[i]);
		if (!CHECK(bset1, hash)) {
			SET(bset1, hash);
			*(h1tail ++) = hash;
		}
	}
	hash = HASH2(VARDATA(str1)[l1 - 1], '\0');
	if (!CHECK(bset1, hash)) {
		SET(bset1, hash);
		*(h1tail ++) = hash;
	}

	for(i = 1; i < l2; ++ i) {
		hash = HASH2(VARDATA(str2)[i - 1], VARDATA(str2)[i]);
		if (!CHECK(bset2, hash)) {
			SET(bset2, hash);
			++ c2;
		}
	}
	hash = HASH2(VARDATA(str2)[l2 - 1], '\0');
	if (!CHECK(bset2, hash)) {
		SET(bset2, hash);
		++ c2;
	}
	unsigned long tot = (unsigned long)(h1tail - h1) + c2;
	for (it = h1; it != h1tail; ++ it) {
		if (CHECK(bset2, *it)) {
			++ ci;
		}
	}
	float8 ret;
	ret = (float8)ci / (float8) (tot - ci);
	PG_RETURN_FLOAT8(ret);
}

