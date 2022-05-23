.schema -- get the sceme of the data
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street"; -- get the information about the theft
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%"; -- get the information about
SELECT destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY minute ASC LIMIT 1; -- get the first flight because that is where the theif went on and get the id of the airport
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY minute ASC LIMIT 1); -- get the city of the airport
