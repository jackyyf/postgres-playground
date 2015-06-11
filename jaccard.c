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
	unsigned long i;
	unsigned long ci = 0, cu = 0;
	RESET(bset1); RESET(bset2);
	if (l1 == 0 || l2 == 0) {
		PG_RETURN_FLOAT8((float8).0);
	}
	SET(bset1, HASH2('\0', VARDATA(str1)[0]));
	SET(bset2, HASH2('\0', VARDATA(str2)[0]));
	for(i = 1; i < l1; ++ i) {
		SET(bset1, HASH2(VARDATA(str1)[i - 1], VARDATA(str1)[i]));
	}
	SET(bset1, HASH2(VARDATA(str1)[l1 - 1], '\0'));
	for(i = 1; i < l2; ++ i) {
		SET(bset2, HASH2(VARDATA(str2)[i - 1], VARDATA(str2)[i]));
	}
	SET(bset2, HASH2(VARDATA(str2)[l2 - 1], '\0'));
	for(i = 0; i < 65536; ++ i) {
		long c1 = CHECK(bset1, i), c2 = CHECK(bset2, i);
		if (c1 || c2) {
			if (c1 && c2) {
				++ ci;
			}
			++ cu;
		}
	}
	float8 ret;
	ret = (float8)ci / (float8) cu;
	PG_RETURN_FLOAT8(ret);
}

