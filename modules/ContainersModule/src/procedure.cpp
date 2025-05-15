#include <QDebug>
#include "procedure.hpp"
// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Procedure::Procedure(int ProcedureID, const QString &name, double fee)
    : ProcedureID(ProcedureID)
    , name(name)
    , fee(fee)
{}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
