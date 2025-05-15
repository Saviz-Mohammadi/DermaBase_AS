#ifndef STARREDPATIENT_H
#define STARREDPATIENT_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct StarredPatient
{
public:
    StarredPatient() = default;
    StarredPatient(int patientID, const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus, bool hasVisited);
    ~StarredPatient() = default;

    int patientID;
    QString firstName;
    QString lastName;
    int birthYear;
    QString phoneNumber;
    QString email;
    QString gender;
    QString maritalStatus;
    bool hasVisited;
};

#endif // STARREDPATIENT_H
