#ifndef PATIENTIMAGESMODEL_H
#define PATIENTIMAGESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include <QUrl>
#include <QFile>
#include <QByteArray>
#include <QImage>
#include <QDir>
#include "database.hpp"
#include "image.hpp"

class PatientImagesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)
    Q_PROPERTY(bool operationIsInProgress READ getOperationIsInProgress NOTIFY operationIsInProgressChanged FINAL)

public:
    explicit PatientImagesModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~PatientImagesModel();

    // PUBLIC Enum
public:
    enum {
        ImageID = Qt::UserRole + 1,
        PatientID,
        Name,
        Data
    };

    // Fields
private:
    Database *m_Database;
    bool m_OperationIsInProgress;
    int m_Row;
    Image m_Image;
    std::vector<Image> m_Data;

    // Signals
signals:
    void databaseChanged();
    void operationIsInProgressChanged();

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE void requestInsertPatientImage(const int patientID, const QUrl &url);
    Q_INVOKABLE void requestRemovePatientImage(const int patientID, const QString &name, const int row);
    Q_INVOKABLE void requestUpdatePatientImageName(const int patientID, const QString &name, const QString &newName, const int row);
    Q_INVOKABLE QUrl getImage(const int row);

    // PRIVATE Methods
private:

    // OVERRIDES
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;

    // PUBLIC Getters
public:
    Database *getDatabase() const;
    bool getOperationIsInProgress() const;

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:
    void setDatabase(Database *newDatabase);

    // PRIVATE Setters
private:
    void setData(std::vector<Image> newData);
};

#endif // PATIENTIMAGESMODEL_H
