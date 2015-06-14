\timing
SELECT ra.address, ap.address, ra.name, ap.phone FROM restaurantaddress ra, addressphone ap WHERE levenshtein_distance(ra.address, ap.address) < 4 AND (ap.address LIKE '%Berkeley%' OR ap.address LIKE '%Oakland%') ORDER BY 1, 2, 3, 4;
