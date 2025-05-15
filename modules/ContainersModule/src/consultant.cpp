#include <QDebug>
#include "Consultant.hpp"
// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Consultant::Consultant(int consultantID, const QString &name, const QString &specialization)
    : consultantID(consultantID)
    , name(name)
    , specialization(specialization)
{}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
