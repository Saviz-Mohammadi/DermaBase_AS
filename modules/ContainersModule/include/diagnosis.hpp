#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct Diagnosis
{
public:
    Diagnosis() = default;
    Diagnosis(int diagnosisID, const QString &name);
    ~Diagnosis() = default;

    int diagnosisID;
    QString name;
};

#endif // DIAGNOSIS_H
