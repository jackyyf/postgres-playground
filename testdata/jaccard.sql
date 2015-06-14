\timing
SELECT rp.phone, ap.phone, rp.name, ap.address FROM restaurantphone rp, addressphone ap WHERE jaccard_index(rp.phone, ap.phone) > .6 AND (ap.address LIKE '%Berkeley%' OR ap.address LIKE '%Oakland%') ORDER BY 1, 2, 3, 4;
