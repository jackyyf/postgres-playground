\timing
SELECT ra.name, rp.name, ra.address, ap.address, rp.phone, ap.phone FROM restaurantphone rp, restaurantaddress ra, addressphone ap WHERE jaccard_index(rp.phone, ap.phone) >= .55 AND levenshtein_distance(rp.name, ra.name) <= 5 AND jaccard_index(ra.address, ap.address) >= .6 AND (ap.address LIKE '%Berkeley%' OR ap.address LIKE '%Oakland%')ORDER BY 1, 2, 3, 4, 5, 6;
