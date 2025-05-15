#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QByteArray>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types instead here, but I cannot figure out how to do it without getting a lot of errors regarding initial value.

struct Image
{
public:
    Image() = default;
    Image(int imageID, const QString &name, const QByteArray &data);
    ~Image() = default;

    int imageID;
    QString name;
    QByteArray data;
};

#endif // IMAGE_H
