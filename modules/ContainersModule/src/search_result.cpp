#include <QDebug>
#include "search_result.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

SearchResult::SearchResult(int patientID, const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus)
    : patientID(patientID)
    , firstName(firstName)
    , lastName(lastName)
    , birthYear(birthYear)
    , phoneNumber(phoneNumber)
    , email(email)
    , gender(gender)
    , maritalStatus(maritalStatus)
{}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
