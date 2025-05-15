-- Specify schema:

USE dermabase;





-- EVENTS (GENERAL):

SET GLOBAL event_scheduler = ON; -- Enable events.

SHOW EVENTS; -- Show all events.

DROP EVENT IF EXISTS event_name; -- Drop certain event.

-- EVENTS (CREATE):

CREATE EVENT IF NOT EXISTS remove_old_patients
ON SCHEDULE EVERY 1 WEEK
STARTS '2024-12-29 00:00:00' -- The moment (date and time) where the event will start working.
DO
    DELETE FROM patients WHERE age > 150; -- If a patient exceeds the age of '150', then most likely they are not of concern anymore.


CREATE EVENT IF NOT EXISTS remove_old_patients
ON SCHEDULE EVERY 1 WEEK
STARTS '2024-12-29 00:00:00' -- The moment (date and time) where the event will start working.
DO
    DELETE FROM patients WHERE deletion_status = TRUE; -- If a patient has been marked for deletion, then remove them from the database. Thanks to the well-designed database, all relevant data from related tables concerning the patient will also be deleted.





-- TRIGGERS (GENERAL):

SHOW TRIGGERS; -- Displays the list of triggers.

DROP TRIGGER IF EXISTS schemaName.triggerName; -- Drop a certain trigger.





-- DROP:

SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE diagnoses;
DROP TABLE treatments;
DROP TABLE procedures;
DROP TABLE consultants;
DROP TABLE labs;
DROP TABLE patients;
DROP TABLE patient_visit_info;
DROP TABLE patient_payment_info;
DROP TABLE starred_patients;
DROP TABLE diagnosis_notes;
DROP TABLE treatment_notes;
DROP TABLE procedure_notes;
DROP TABLE patient_diagnoses;
DROP TABLE patient_treatments;
DROP TABLE patient_procedures;
DROP TABLE patient_consultations;
DROP TABLE patient_lab_tests;
DROP TABLE patient_images;

SET FOREIGN_KEY_CHECKS = 1;
