-- Schema:

USE dermabase;





-- Patients:

CREATE TABLE IF NOT EXISTS `patients` (
  `patient_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key for the table to uniquely identify each patient.',
  `first_name` VARCHAR(30) NOT NULL COMMENT 'The first name of the patient.',
  `last_name` VARCHAR(30) NOT NULL COMMENT 'The last name of the patient.',
  `birth_year` SMALLINT UNSIGNED NOT NULL COMMENT 'The patient''s year of birth.',
  `phone_number` VARCHAR(20) NOT NULL COMMENT 'The phone number of the patient. (According to the international standard for phone numbers (ITU-T E.164), phone numbers can be up to 15 digits long. This includes the country code, area code, and the subscriber''s number, but does not include any formatting characters like dashes, spaces, or parentheses. Therefore, I made the size 20 to account for any additional symbols and characters)',
  `email` VARCHAR(320) DEFAULT NULL COMMENT 'The email of the patient. (According to ''RFC 5321'' the maximum size can be 320 characters. )',
  `gender` ENUM('مرد', 'زن', 'نامشخص') DEFAULT 'نامشخص' COMMENT 'The patient''s gender.',
  `marital_status` ENUM('مجرد', 'متاهل', 'نامشخص') DEFAULT 'نامشخص' COMMENT 'The patient''s marital status.',
  `is_marked_for_deletion` BOOLEAN DEFAULT FALSE COMMENT 'Used as a flag to determine if the patient must be deleted.',
  
  PRIMARY KEY (`patient_id`),
  
  UNIQUE (first_name, last_name, birth_year) -- If two records are to have the exact same combination of 'first_name', 'last_name', and 'birth_year', then insertion will be prevented via this unique composite key.

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table will keep track of patients and their basic data.';


CREATE TABLE IF NOT EXISTS `patient_visit_info` (
  `patient_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The ID of the patient. Matches the ''patient_id'' PRIMARY KEY in the ''patients'' table.',
  `number_of_previous_visits` SMALLINT UNSIGNED DEFAULT 0 COMMENT 'The number of times the patient previously visited the dermatologist.',
  `first_visit_date` DATE DEFAULT NULL COMMENT 'The patient''s first visit date.',
  `recent_visit_date` DATE DEFAULT NULL COMMENT 'The patient''s recent visit date. (Useful for calculating how much time has passed since the last visit)',
  `expected_visit_date` DATE DEFAULT NULL COMMENT 'The patient''s expected visit date. (Useful for sending notification reminders)',
  
  PRIMARY KEY (`patient_id`),

  CONSTRAINT `patient_visit_info_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients` (`patient_id`) ON DELETE CASCADE
  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table will keep track of patient''s visit information.';


CREATE TABLE IF NOT EXISTS `patient_payment_info` (
  `patient_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The ID of the patient. Matches the ''patient_id'' PRIMARY KEY in the ''patients'' table.',
  `service_price` DECIMAL(10, 3) DEFAULT 0.000 COMMENT 'The price of the health care service provided to the patient.',
  `paid_price` DECIMAL(10, 3) DEFAULT 0.000 COMMENT 'The amount that the patient has paid for the health care service.',
  
  PRIMARY KEY (`patient_id`),

  CONSTRAINT `patient_payment_info_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients` (`patient_id`) ON DELETE CASCADE
  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table will keep track of patient''s payment information.';


CREATE TABLE IF NOT EXISTS `starred_patients` (
  `patient_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The ID of the patient. Matches the ''patient_id'' PRIMARY KEY in the ''patients'' table.',
  `has_visited` BOOLEAN DEFAULT FALSE COMMENT 'The visit status of each starred patient. (Useful for determining whether a patient in the starred list has truly completed their visit or simply arrived and left)',
  
  PRIMARY KEY (`patient_id`),
  
  CONSTRAINT `starred_patients_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients` (`patient_id`) ON DELETE CASCADE
  
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table will keep track of starred patients added by users.';





-- Diagnoses:

CREATE TABLE IF NOT EXISTS `diagnoses` (
  `diagnosis_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key for the table to uniquely identify each diagnosis.',
  `name` VARCHAR(60) NOT NULL COMMENT 'The name of the diagnosis.',
  `is_active` BOOLEAN DEFAULT TRUE COMMENT 'Indicates if the diagnosis is currently offered and assignable.',
  
  PRIMARY KEY (`diagnosis_id`)

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table will keep track of all diagnosis names that can be assigned to a patient. If a diagnosis is permanently deleted (hard delete), the system will automatically remove all associations between the diagnosis and any affected patients. However, it is recommended to instead alter the ''active_status'' status of the diagnosis (soft delete), as this approach preserves data integrity while deactivating the diagnosis';


CREATE TABLE IF NOT EXISTS `patient_diagnoses` (
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''patients'' table primary key.',
  `diagnosis_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''diagnoses'' table primary key.',
  
  PRIMARY KEY (`diagnosis_id`,`patient_id`),
  
  KEY `patient_diagnoses_patient_fk_index` (`patient_id`),
  KEY `patient_diagnoses_diagnosis_fk_index` (`diagnosis_id`),
  
  CONSTRAINT `patient_diagnoses_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients` (`patient_id`),
  CONSTRAINT `patient_diagnoses_diagnosis_fk` FOREIGN KEY (`diagnosis_id`) REFERENCES `diagnoses` (`diagnosis_id`)

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='A table that manages the list of diagnoses assigned to the each patient.';


CREATE TABLE IF NOT EXISTS `diagnosis_notes` (
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'The ID of the patient. Matches the ''patient_id'' PRIMARY KEY in the ''patients'' table.',
  `note` TEXT COMMENT 'The diagnosis note written by the dermatologist.',
  
  PRIMARY KEY (`patient_id`),
  
  CONSTRAINT `diagnosis_notes_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients`(`patient_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table stores diagnosis notes for each patient.';





-- Treatments:

CREATE TABLE IF NOT EXISTS `treatments` (
  `treatment_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key for the table to uniquely identify each treatment.',
  `name` VARCHAR(60) NOT NULL COMMENT 'The name of the treatment.',
  `is_active` BOOLEAN DEFAULT TRUE COMMENT 'Indicates if the treatment is currently offered and assignable.',
  
  PRIMARY KEY (`treatment_id`)

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='The table will keep track of all treatment names that can be assigned to a patient. If a treatment is permanently deleted (hard delete), the system will automatically remove all associations between the treatment and any affected patients. However, it is recommended to instead alter the ''active_status'' status of the treatment (soft delete), as this approach preserves data integrity while deactivating the treatment';


CREATE TABLE IF NOT EXISTS `patient_treatments` (
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''patients'' table primary key.',
  `treatment_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''treatments'' table primary key.',
  
  PRIMARY KEY (`patient_id`,`treatment_id`),
  
  KEY `patient_treatments_patient_fk_index` (`patient_id`),
  KEY `patient_treatments_treatment_fk_index` (`treatment_id`),
  
  CONSTRAINT `patient_treatments_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients` (`patient_id`) ON DELETE CASCADE,
  CONSTRAINT `patient_treatments_treatment_fk` FOREIGN KEY (`treatment_id`) REFERENCES `treatments` (`treatment_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='A table that manages the list of treatments assigned to the each patient.';


CREATE TABLE IF NOT EXISTS `treatment_notes` (
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'The ID of the patient. Matches the ''patient_id'' PRIMARY KEY in the ''patients'' table.',
  `note` TEXT COMMENT 'The treatment note written by the dermatologist.',
  
  PRIMARY KEY (`patient_id`),
  
  CONSTRAINT `treatment_notes_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients`(`patient_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table stores treatment notes for each patient.';





-- Procedures:

CREATE TABLE IF NOT EXISTS `procedures` (
  `procedure_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key for the table to uniquely identify each procedure.',
  `name` VARCHAR(60) NOT NULL COMMENT 'The name of the procedure.',
  `is_active` BOOLEAN DEFAULT TRUE COMMENT 'Indicates if the procedure is currently offered and assignable.',
  
  PRIMARY KEY (`procedure_id`)

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='The table will keep track of all procedure names that can be assigned to a patient. If a procedure is permanently deleted (hard delete), the system will automatically remove all associations between the procedure and any affected patients. However, it is recommended to instead alter the ''active_status'' status of the procedure (soft delete), as this approach preserves data integrity while deactivating the procedure';


CREATE TABLE IF NOT EXISTS `patient_procedures` (
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''patients'' table primary key.',
  `procedure_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''procedures'' table primary key.',
  `procedure_fee` DECIMAL(10, 3) DEFAULT 0.000 COMMENT 'The custom fee for this procedure.',
  
  PRIMARY KEY (`patient_id`,`procedure_id`),
  
  KEY `patient_procedures_patient_fk_index` (`patient_id`),
  KEY `patient_procedures_procedure_index` (`procedure_id`),
  
  CONSTRAINT `patient_procedures_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients` (`patient_id`) ON DELETE CASCADE,
  CONSTRAINT `patient_procedures_procedure_fk` FOREIGN KEY (`procedure_id`) REFERENCES `procedures` (`procedure_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='A table that manages the list of procedures assigned to the each patient.';


CREATE TABLE IF NOT EXISTS `procedure_notes` (
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'The ID of the patient. Matches the ''patient_id'' PRIMARY KEY in the ''patients'' table.',
  `note` TEXT COMMENT 'The procedure note written by the dermatologist.',
  
  PRIMARY KEY (`patient_id`),
  
  CONSTRAINT `procedure_notes_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients`(`patient_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='This table stores procedure notes for each patient.';





-- Consultants:

CREATE TABLE IF NOT EXISTS `consultants` (
  `consultant_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key to uniquely identify each consultant.',
  `name` VARCHAR(60) NOT NULL COMMENT 'The name of the consultant.',
  `specialization` ENUM('Endocrinologist', 'Gasteroenterologist', 'GYN', 'Hematologist', 'Infectious Diseases', 'Ophthalmologist', 'Orthopedist', 'Pediatrics', 'Pulmonologist', 'Rheumatologist', 'Surgeon', 'Urologist', 'Cardiologist', 'Radiologist') NOT NULL COMMENT 'The specialization of the consultant.',
  `is_active` BOOLEAN DEFAULT TRUE COMMENT 'Indicates if the consultant is currently offered and assignable.',
  
  PRIMARY KEY (`consultant_id`)

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='The table will keep track of all consultant names and specializations. If a consultant is permanently deleted (hard delete), the system will automatically remove all associations between the consultant and any affected patients. However, it is recommended to instead alter the ''active_status'' status of the consultant (soft delete), as this approach preserves data integrity while deactivating the consultant.';


CREATE TABLE IF NOT EXISTS `patient_consultations` (
  `consultation_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key for the table to uniquely identify each consultation.',
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''patients'' table primary key.',
  `consultant_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''consultants'' table primary key.',
  `consultation_date` DATE DEFAULT NULL COMMENT 'The date the consultation was conducted.',
  `consultation_outcome` TEXT DEFAULT NULL COMMENT 'The outcome (notes) of the consultation.',
  
  PRIMARY KEY (`consultation_id`),
  
  KEY `patient_consultations_patient_fk_index` (`patient_id`),
  KEY `patient_consultations_consultant_index` (`consultant_id`),
  
  CONSTRAINT `patient_consultations_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients`(`patient_id`) ON DELETE CASCADE,
  CONSTRAINT `patient_consultations_consultant_fk` FOREIGN KEY (`consultant_id`) REFERENCES `consultants`(`consultant_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='A table that manages the list of consultations assigned to the each patient.';





-- Labs:

CREATE TABLE IF NOT EXISTS `labs` (
  `lab_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key to uniquely identify each lab.',
  `name` VARCHAR(60) NOT NULL COMMENT 'The name of the lab.',
  `specialization` ENUM('Skin Biopsy') NOT NULL COMMENT 'The specialization of the lab.',
  `is_active` BOOLEAN DEFAULT TRUE COMMENT 'Indicates if the lab is currently offered and assignable.',
  
  PRIMARY KEY (`lab_id`)

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='The table will keep track of all lab names and specializations. If a lab is permanently deleted (hard delete), the system will automatically remove all associations between the lab and any affected patients. However, it is recommended to instead alter the ''active_status'' status of the lab (soft delete), as this approach preserves data integrity while deactivating the lab.';


CREATE TABLE IF NOT EXISTS `patient_lab_tests` (
  `lab_test_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key for the table to uniquely identify each lab test.',
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''patients'' table primary key.',
  `lab_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''labs'' table primary key.',
  `lab_test_date` DATE DEFAULT NULL COMMENT 'The date the lab test was conducted.',
  `lab_test_outcome` TEXT DEFAULT NULL COMMENT 'The outcome (notes) of the lab test.',
  `properties` JSON DEFAULT NULL COMMENT 'The properties of the lab test.',
  
  PRIMARY KEY (`lab_test_id`),
  
  KEY `patient_lab_tests_patient_fk_index` (`patient_id`),
  KEY `patient_lab_tests_lab_index` (`lab_id`),
  
  CONSTRAINT `patient_lab_tests_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients`(`patient_id`) ON DELETE CASCADE,
  CONSTRAINT `patient_lab_tests_lab_fk` FOREIGN KEY (`lab_id`) REFERENCES `labs`(`lab_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='A table that manages the list of lab tests assigned to the each patient.';





-- Images:

CREATE TABLE IF NOT EXISTS `patient_images` (
  `image_id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The primary key for the table to uniquely identify each image.',
  `patient_id` INT UNSIGNED NOT NULL COMMENT 'A foreign key reference to the ''patients'' table primary key.',
  `image_name` VARCHAR(60) COMMENT 'The name of the image. (Used to identify the image in the application. This can be anything: custom name, file name, etc.)',
  `image_data` MEDIUMBLOB COMMENT 'The byte data of the image.',
  
  PRIMARY KEY (`image_id`),
  
  KEY `patient_images_patient_fk_index` (`patient_id`),
  
  CONSTRAINT `patient_images_patient_fk` FOREIGN KEY (`patient_id`) REFERENCES `patients`(`patient_id`) ON DELETE CASCADE

) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='A table that manages the list of images assigned to the each patient.';





-- Triggers:

DELIMITER $$

CREATE TRIGGER add_patient_visit_info

AFTER INSERT ON `patients` FOR EACH ROW
BEGIN
    INSERT INTO `patient_visit_info` (`patient_id`)
    VALUES (NEW.patient_id);
END$$

DELIMITER ;


DELIMITER $$

CREATE TRIGGER add_patient_payment_info

AFTER INSERT ON `patients` FOR EACH ROW
BEGIN
    INSERT INTO `patient_payment_info` (`patient_id`)
    VALUES (NEW.patient_id);
END$$

DELIMITER ;


DELIMITER $$

CREATE TRIGGER add_diagnosis_note

AFTER INSERT ON `patients` FOR EACH ROW
BEGIN
    INSERT INTO `diagnosis_notes` (`patient_id`, `note`)
    VALUES (NEW.patient_id, '');
END$$

DELIMITER ;


DELIMITER $$

CREATE TRIGGER add_treatment_note

AFTER INSERT ON `patients` FOR EACH ROW
BEGIN
    INSERT INTO `treatment_notes` (`patient_id`, `note`)
    VALUES (NEW.patient_id, '');
END$$

DELIMITER ;


DELIMITER $$

CREATE TRIGGER add_procedure_note

AFTER INSERT ON `patients` FOR EACH ROW
BEGIN
    INSERT INTO `procedure_notes` (`patient_id`, `note`)
    VALUES (NEW.patient_id, '');
END$$

DELIMITER ;
