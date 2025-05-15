#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct Procedure
{
public:
    Procedure() = default;
    Procedure(int ProcedureID, const QString &name, double fee);
    ~Procedure() = default;

    int ProcedureID;
    QString name;
    double fee;
};

#endif // PROCEDURE_H
