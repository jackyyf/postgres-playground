CREATE FUNCTION levenshtein_distance(text, text) RETURNS INT
AS 'libplayground', 'levenshtein_distance' LANGUAGE C STRICT;
CREATE FUNCTION jaccard_index(text, text) RETURNS DOUBLE PRECISION
AS 'libplayground', 'jaccard_index' LANGUAGE C STRICT;
