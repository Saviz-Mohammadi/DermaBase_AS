#ifndef LAB_H
#define LAB_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct Lab
{
public:
    Lab() = default;
    Lab(int labID, const QString &name, const QString &specialization);
    ~Lab() = default;

    int labID;
    QString name;
    QString specialization;
};

#endif // LAB_H
