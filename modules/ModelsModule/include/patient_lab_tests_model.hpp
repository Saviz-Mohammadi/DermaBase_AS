#ifndef PATIENTLABTESTSMODEL_H
#define PATIENTLABTESTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "lab_test.hpp"

class PatientLabTestsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)
    Q_PROPERTY(bool operationIsInProgress READ getOperationIsInProgress NOTIFY operationIsInProgressChanged FINAL)

public:
    explicit PatientLabTestsModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~PatientLabTestsModel();

    // PUBLIC Enum
public:
    enum {
        LabTestID = Qt::UserRole + 1,
        PatientID,
        LabID,
        Date,
        Outcome,
        Name,
        Specialization,
        CBC,
        WBC,
        Hgb,
        Ferritin,
        ESR,
        Na,
        K,
        Mg,
        VitaminD,
        FBS,
        TG,
        Cholestrol,
        AST,
        ALT,
        ALKPh,
        BUN,
        Cr,
        UA,
        SE_OB,
        SE_OP,
        H_Pylori_Ab,
        H_Pylori_Ag_SE,
        Tuberculin_test,
        Pathergy_test,
        Sonography,
        TSH,
        LH,
        FSH,
        DHEAS,
        OH_P_17,
        Prolactine,
        Testosterone,
        Hepatitis_Ag,
        Hepatitis_Ab,
        ANA,
        Anti_DS_Ab,
        Anti_SCL70_Ab,
        IgE,
    };

    // Fields
private:
    Database *m_Database;
    bool m_OperationIsInProgress;
    int m_Row;
    LabTest m_LabTest;
    std::vector<LabTest> m_Data;

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
    Q_INVOKABLE void requestInsertPatientLabTest(const int patientID, const int labID);
    Q_INVOKABLE void requestRemovePatientLabTest(const int row);
    Q_INVOKABLE void requestUpdatePatientLabTest(const int labTestID, const QString &date, const QString &outcome,
                                                 int CBC,
                                                 int WBC,
                                                 int Hgb,
                                                 int Ferritin,
                                                 int ESR,
                                                 int Na,
                                                 int K,
                                                 int Mg,
                                                 int VitaminD,
                                                 int FBS,
                                                 int TG,
                                                 int Cholestrol,
                                                 int AST,
                                                 int ALT,
                                                 int ALKPh,
                                                 int BUN,
                                                 int Cr,
                                                 int UA,
                                                 int SE_OB,
                                                 int SE_OP,
                                                 int H_Pylori_Ab,
                                                 int H_Pylori_Ag_SE,
                                                 int Tuberculin_test,
                                                 int Pathergy_test,
                                                 int Sonography,
                                                 int TSH,
                                                 int LH,
                                                 int FSH,
                                                 int DHEAS,
                                                 int OH_P_17,
                                                 int Prolactine,
                                                 int Testosterone,
                                                 int Hepatitis_Ag,
                                                 int Hepatitis_Ab,
                                                 int ANA,
                                                 int Anti_DS_Ab,
                                                 int Anti_SCL70_Ab,
                                                 int IgE, const int row);

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
    void setData(std::vector<LabTest> newData);
};

#endif // PATIENTLABTESTSMODEL_H
