#include <QDebug>
#include "starred_patient.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

StarredPatient::StarredPatient(int patientID, const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus, bool hasVisited)
    : patientID(patientID)
    , firstName(firstName)
    , lastName(lastName)
    , birthYear(birthYear)
    , phoneNumber(phoneNumber)
    , email(email)
    , gender(gender)
    , maritalStatus(maritalStatus)
    , hasVisited(hasVisited)
{}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
