#ifndef CONSULTANT_H
#define CONSULTANT_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct Consultant
{
public:
    Consultant() = default;
    Consultant(int consultantID, const QString &name, const QString &specialization);
    ~Consultant() = default;

    int consultantID;
    QString name;
    QString specialization;
};

#endif // CONSULTANT_H
