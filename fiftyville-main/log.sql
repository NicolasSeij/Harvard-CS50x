-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Getting the first report of crime scene.
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Humphrey Street" AND description like "%duck%";

-- Get more info. from the three witnesses
SELECT name, transcript FROM interviews
WHERE transcript LIKE "%bakery%" AND day = 28;

-- From the interview, there are 3 hints:
-- 1. within ten minutes of the theft (10:15am) >> get into a car in the bakery parking lot and drive away.
    -- Checking car plate where enter (during the day) and exit (within 10 mins of theft)
SELECT people.name, people.license_plate, bakery_security_logs.activity
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND hour = 10 AND minute > 15 AND minute < 15 + 10 AND activity = "exit";

-- 2. Earlier this morning - by the ATM (on Leggett Street) >> the thief withdrawed money.
    -- Match transaction with account owner (thief)
SELECT name, atm_transactions.transaction_type
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.transaction_type = "withdraw" AND atm_transactions.atm_location = "Leggett Street" AND day = 28;

-- 3. thief talk to phone planning to take the earliest flight out of Fiftyville tomorrow.
        -- Getting call that less than 60 sec
UPDATE phone_calls
SET caller_name = people.name FROM people
WHERE phone_calls.caller = people.phone_number;

UPDATE phone_calls
SET receiver_name = people.name FROM people
WHERE phone_calls.receiver = people.phone_number;

SELECT caller, caller_name, receiver, receiver_name FROM phone_calls
WHERE day = 28 AND month = 7 AND duration <= 60;

-- Getting the earliest flight
UPDATE flights
SET origin_airport_id = airports.city FROM airports
WHERE origin_airport_id = airports.id;

UPDATE flights
SET destination_airport_id = airports.city FROM airports
WHERE destination_airport_id = airports.id;

SELECT flights.id, origin_airport_id, destination_airport_id, month, day, hour, minute
FROM flights JOIN airports ON flights.origin_airport_id = airports.city
WHERE flights.day >= 28 AND airports.city = "Fiftyville"
ORDER BY hour LIMIT 1;

-- Checking passenger passport list of flight id
SELECT flights.destination_airport_id, name, phone_number, license_plate
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    WHERE flights.id = 36
    ORDER BY flights.hour;

-- Getting name that shows in all table
SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    WHERE (flights.id = 36 AND flights.day = 29)
    AND name IN
        (SELECT caller_name FROM phone_calls
        WHERE day = 28 AND month = 7 AND duration <= 60)
    AND name IN
        (SELECT name FROM people
        JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
        WHERE day = 28 AND hour = 10 AND minute > 15 AND minute < 15 + 10 AND activity = "exit")
    AND name IN
        (SELECT name FROM people
        JOIN bank_accounts ON people.id = bank_accounts.person_id
            JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
            WHERE atm_transactions.transaction_type = "withdraw" AND atm_transactions.atm_location = "Leggett Street" AND day = 28);
