#include "postgres.h"
#include <stdlib.h>
#include <string.h>

unsigned long text_len(text *textptr) {
	return VARSIZE(textptr) - VARHDRSZ;
}

char *to_cptr(text *textptr) {
	unsigned long len = text_len(textptr);
	char *ret = palloc(len + 1);
	if (ret == NULL) {
		elog(ERROR, "Allocation failed.");
		abort();
	}
	memcpy(ret, VARDATA(textptr), len);
	ret[len] = 0;
	return ret;
}
