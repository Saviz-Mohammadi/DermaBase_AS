#include <QDebug>
#include "date.hpp"

Date *Date::m_Instance = Q_NULLPTR;

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Date::Date(QObject *parent, const QString &name)
    : QObject{parent}
{
    this->setObjectName(name);

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

Date::~Date()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

Date *Date::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    if (!m_Instance)
    {
        m_Instance = new Date();
    }

    return (m_Instance);
}

Date *Date::cppInstance(QObject *parent)
{
    if (m_Instance)
    {
        return (qobject_cast<Date *>(Date::m_Instance));
    }

    auto instance = new Date(parent);
    m_Instance = instance;

    return (instance);
}

// NOTE (SAVIZ): Not needed. However, provided just in case.
void Date::Init()
{
    // Init resources;
}

// NOTE (SAVIZ): In Qt, this isn't necessary due to its parent-child memory management system. However, in standard C++, it's a good practice to either explicitly call this when we're done with the object or ensure it gets invoked within the destructor.
void Date::ShutDown()
{
    delete (m_Instance);

    m_Instance = Q_NULLPTR;
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Methods
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

QCalendar::YearMonthDay Date::gregorianToJalali(QCalendar::YearMonthDay gregorianYMD)
{
    QCalendar calendarGregorian(QCalendar::System::Gregorian);
    QCalendar calendarJalali(QCalendar::System::Jalali);

    QDate gregorianDate(gregorianYMD.year, gregorianYMD.month, gregorianYMD.day);

    QCalendar::YearMonthDay ymd = calendarJalali.partsFromDate(gregorianDate);

    return (ymd);
}

QCalendar::YearMonthDay Date::jalaliToGregorian(QCalendar::YearMonthDay jalaliYMD)
{
    QCalendar calendarJalali(QCalendar::System::Jalali);
    QCalendar calendarGregorian(QCalendar::System::Gregorian);

    QDate gregorianDate = calendarJalali.dateFromParts(jalaliYMD.year, jalaliYMD.month, jalaliYMD.day);

    QCalendar::YearMonthDay ymd = calendarGregorian.partsFromDate(gregorianDate);

    return (ymd);
}

QString Date::gregorianToJalali(QDate georgian)
{
    QCalendar::YearMonthDay gregorianYMD(georgian.year(), georgian.month(), georgian.day());

    QCalendar::YearMonthDay jaliliYMD = Date::cppInstance()->gregorianToJalali(gregorianYMD);

    QString DateString = QString("%1-%2-%3")
                                       .arg(jaliliYMD.year, 4, 10, QChar('0'))
                                       .arg(jaliliYMD.month, 2, 10, QChar('0'))
                                       .arg(jaliliYMD.day, 2, 10, QChar('0'));

    return (DateString);
}

QString Date::calculateJalaliAge(quint32 birthYear)
{
    QCalendar::YearMonthDay gregorianYMD(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());
    QCalendar::YearMonthDay newJalili = gregorianToJalali(gregorianYMD);

    QString result = QString::number(newJalili.year - birthYear);

    return (result);
}

QString Date::differenceToDateJalali(int year, int month, int day)
{
    QCalendar::YearMonthDay gregorianYMD(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());
    QCalendar::YearMonthDay newJalili = gregorianToJalali(gregorianYMD);
    QDate currentDate(newJalili.year, newJalili.month, newJalili.day);

    QString result;



    int years = currentDate.year() - year;
    int months = currentDate.month() - month;
    int days = currentDate.day() - day;

    // Adjust for negative days
    if (days < 0) {
        QDate prevMonth = currentDate.addMonths(-1);
        days += prevMonth.daysInMonth();
        months -= 1;
    }

    // Adjust for negative months
    if (months < 0) {
        months += 12;
        years -= 1;
    }


    result = QString("(%1 %2) - (%3 %4) - (%5 %6)") // The Arguments on the left hand side will be the plural form:
                .arg(years <= 0 ? 0 : years)
                .arg(years == 1 ? "سال" : "سال")
                .arg(months <= 0 ? 0 : months)
                .arg(months == 1 ? "ماه" : "ماه")
                .arg(days <= 0 ? 0 : days)
                .arg(days == 1 ? "روز" : "روز");



    return (result);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
