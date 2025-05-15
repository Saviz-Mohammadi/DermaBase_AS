#include <QDebug>
#include "consultation.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Consultation::Consultation(const int consultationID, const int patientID, const int consultantID, const QString &date, const QString &outcome, const QString &name, const QString &specialization)
    : consultationID(consultationID)
    , patientID(patientID)
    , consultantID(consultantID)
    , date(date)
    , outcome(outcome)
    , name(name)
    , specialization(specialization)
{}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
