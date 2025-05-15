#ifdef QT_DEBUG
    #include <QDebug>
#endif

#include "images_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

ImagesModel::ImagesModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_List{QVariantList()}
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

ImagesModel::~ImagesModel()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Methods
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void ImagesModel::addImage(const QUrl &url)
{
    // First make a check and see if file name already exists:
    bool existingStatus = false;

    QFileInfo fileInfo(url.toLocalFile());

    for (const auto &item : m_List)
    {
        QVariantMap imageMap = item.toMap();

        if (imageMap.value("image_name").toString() == fileInfo.fileName()) {
            existingStatus = true;
        }
    }

    if(existingStatus == true)
    {
        emit imageAddedStatus(false, "یک فایل تصویر با همان نام قبلاً وجود دارد.");

        return;
    }

    beginInsertRows(QModelIndex(), m_List.size(), m_List.size());

    QFile file(url.toLocalFile());

    if (!file.open(QIODevice::ReadOnly))
    {
#ifdef QT_DEBUG
        qDebug() << "Could not open file:" << url.toLocalFile();
#endif

        return;
    }

    QByteArray imageData = file.readAll();

    file.close();

    QVariantMap imageMap;

    imageMap["image_name"] = url.fileName();
    imageMap["image_data"] = imageData;

    m_List.append(imageMap);

    endInsertRows();
}

void ImagesModel::removeImageByIndex(const int index)
{
    if (index < 0 || index >= m_List.size())
    {
#ifdef QT_DEBUG
        qDebug() << "Invalid index" << index << ". Cannot remove element.";
#endif

        return;
    }

    beginRemoveRows(QModelIndex(), index, index);

    m_List.removeAt(index);

    endRemoveRows();
}

QUrl ImagesModel::getImage(const int index)
{
    if (index < 0 || index >= m_List.size())
    {
#ifdef QT_DEBUG
        qDebug() << "Invalid index" << index << ". Cannot get element.";
#endif

        return (QUrl());
    }

    QVariantMap imageMap = m_List.at(index).toMap();
    QString fileName = imageMap["image_name"].toString();
    int pos = fileName.lastIndexOf('.');
    QString extension = "png";
    if (pos != -1)
    {
        extension = fileName.mid(pos + 1);
    }

    QByteArray imageData = imageMap["image_data"].toByteArray();
    QImage image;

    if (!image.loadFromData(imageData))
    {
#ifdef QT_DEBUG
        qDebug() << "Failed to load image";
#endif

        return QUrl();
    }

    QDir dir("./cache/images");
    QString filePath = dir.absolutePath() + "temp_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + "." + extension;

    // NOTE (SAVIZ): nullptr forces the QImage to decide for itself what the best format for the image file will be.
    if (!image.save(filePath, nullptr))
    {
#ifdef QT_DEBUG
        qDebug() << "Failed to save to path: " << filePath;
#endif

        return QUrl();
    }

    return QUrl::fromLocalFile(filePath);  // Convert file path to QUrl
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Getters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

QVariantList ImagesModel::getList() const
{
    return (m_List);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void ImagesModel::setList(QVariantList newList)
{
    beginResetModel();

    m_List = newList;

    endResetModel();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int ImagesModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return (0);
    }

    return (m_List.length());
}

QVariant ImagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const QVariantMap& imageMap = m_List.at(index.row()).toMap();

    switch (role)
    {
    case NAME:
        return (imageMap["image_name"].toString());
        break;
    default:
        return (imageMap["image_data"].toByteArray());
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> ImagesModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { NAME, "image_name" },
        { DATA, "image_data"}
    };

    return (roleMapping);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
