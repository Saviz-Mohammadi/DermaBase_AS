#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct Consultation
{
public:
    Consultation() = default;
    Consultation(const int consultationID, const int patientID, const int consultantID, const QString &date, const QString &outcome, const QString &name, const QString &specialization);
    ~Consultation() = default;

    int consultationID;
    int patientID;
    int consultantID;
    QString date;
    QString outcome;
    QString name;
    QString specialization;
};

#endif // CONSULTATION_H
