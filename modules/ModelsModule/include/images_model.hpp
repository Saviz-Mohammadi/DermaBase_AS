#ifndef IMAGES_MODEL_HPP
#define IMAGES_MODEL_HPP

#include <QAbstractListModel>
#include <QVariantList>
#include <QVariantMap>
#include <QBuffer>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QImageReader>

class ImagesModel : public QAbstractListModel
{
    Q_OBJECT

    // PUBLIC Enums
public:
    enum {
        NAME,
        DATA
    };

public:
    explicit ImagesModel(QObject *parent = nullptr);
    ~ImagesModel();

    // Fields
private:
    QVariantList m_List;

    // Signals
signals:
    void imageAddedStatus(bool status, QString message);

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE void addImage(const QUrl &url);
    Q_INVOKABLE void removeImageByIndex(const int index);
    Q_INVOKABLE QUrl getImage(const int index);

    // PRIVATE Methods
private:

    // PUBLIC Getters
public:
    Q_INVOKABLE QVariantList getList() const;

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:
    Q_INVOKABLE void setList(QVariantList newList);

    // PRIVATE Setters
private:

    // OVERRIDES
protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // IMAGES_MODEL_HPP
