#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct SearchResult
{
public:
    SearchResult() = default;
    SearchResult(int patientID, const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus);
    ~SearchResult() = default;

    int patientID;
    QString firstName;
    QString lastName;
    int birthYear;
    QString phoneNumber;
    QString email;
    QString gender;
    QString maritalStatus;
};

#endif // SEARCHRESULT_H
