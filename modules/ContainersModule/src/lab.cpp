#include <QDebug>
#include "lab.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Lab::Lab(int labID, const QString &name, const QString &specialization)
    : labID(labID)
    , name(name)
    , specialization(specialization)
{}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
