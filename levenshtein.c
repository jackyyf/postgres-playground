#include "postgres.h"
#include "fmgr.h"
#include "util.h"

PG_FUNCTION_INFO_V1(levenshtein_distance);

Datum levenshtein_distance(PG_FUNCTION_ARGS) {
	/* According to slides: both arguments contain no more than 100 ASCII characters. */
	static unsigned long dist[128][128];
	text *str1 = (text *)PG_GETARG_TEXT_P(0);
	text *str2 = (text *)PG_GETARG_TEXT_P(1);
	unsigned long l1 = text_len(str1), l2 = text_len(str2);
	unsigned long i, j;
	for(i = 0; i < l1; ++ i) dist[i][0] = i;
	for(i = 1; i < l2; ++ i) dist[0][i] = i;
	for(i = 1; i < l1; ++ i) {
		for(j = 1; j < l2; ++ j) {
			if (VARDATA(str1)[i] == VARDATA(str2)[j]) {
				dist[i][j] = dist[i - 1][j - 1];
			} else {
				dist[i][j] = min3(dist[i - 1][j], dist[i][j - 1], dist[i - 1][j - 1]) + 1;
			}
		}
	}
	PG_RETURN_INT32(dist[l1 - 1][l2 - 1]);
}
