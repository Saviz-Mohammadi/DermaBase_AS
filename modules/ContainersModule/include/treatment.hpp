#ifndef TREATMENT_H
#define TREATMENT_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct Treatment
{
public:
    Treatment() = default;
    Treatment(int treatmentID, const QString &name);
    ~Treatment() = default;

    int treatmentID;
    QString name;
};

#endif // TREATMENT_H
