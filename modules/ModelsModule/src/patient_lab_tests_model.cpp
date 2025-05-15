#include <QDebug>
#include "patient_lab_tests_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

PatientLabTestsModel::PatientLabTestsModel(QObject *parent, const QString &name)
    : QAbstractListModel{parent}
    , m_Database(nullptr)
    , m_OperationIsInProgress(false)
    , m_Row(-1)
    , m_Data()
{
    this->setObjectName(name);

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

PatientLabTestsModel::~PatientLabTestsModel()
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

void PatientLabTestsModel::requestInsertPatientLabTest(const int patientID, const int labID)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Database->insertPatientLabTest(patientID, labID);
}

void PatientLabTestsModel::requestRemovePatientLabTest(const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;
    m_Database->removePatientLabTest(m_Data[row].labTestID);
}

void PatientLabTestsModel::requestUpdatePatientLabTest(const int labTestID, const QString &date, const QString &outcome, int CBC, int WBC, int Hgb, int Ferritin, int ESR, int Na, int K, int Mg, int VitaminD, int FBS, int TG, int Cholestrol, int AST, int ALT, int ALKPh, int BUN, int Cr, int UA, int SE_OB, int SE_OP, int H_Pylori_Ab, int H_Pylori_Ag_SE, int Tuberculin_test, int Pathergy_test, int Sonography, int TSH, int LH, int FSH, int DHEAS, int OH_P_17, int Prolactine, int Testosterone, int Hepatitis_Ag, int Hepatitis_Ab, int ANA, int Anti_DS_Ab, int Anti_SCL70_Ab, int IgE, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;

    LabTest labTest(
        labTestID,
        m_Data[m_Row].patientID,
        m_Data[m_Row].labID,
        date,
        outcome,
        m_Data[m_Row].name,
        m_Data[m_Row].specialization,
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
        IgE
    );

    m_LabTest = labTest;

    m_Database->updatePatientLabTest(
        labTest
    );
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int PatientLabTestsModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant PatientLabTestsModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == LabTestID)
    {
        return(m_Data[row].labTestID);
    }

    else if (role == PatientID)
    {
        return(m_Data[row].patientID);
    }

    else if (role == LabID)
    {
        return(m_Data[row].labID);
    }

    else if (role == Date)
    {
        return(m_Data[row].date);
    }

    else if (role == Outcome)
    {
        return(m_Data[row].outcome);
    }

    else if (role == Name)
    {
        return(m_Data[row].name);
    }

    else if (role == Specialization)
    {
        return(m_Data[row].specialization);
    }

    else if (role == CBC)
    {
        return(m_Data[row].CBC);
    }

    else if (role == WBC)
    {
        return(m_Data[row].WBC);
    }

    else if (role == Hgb)
    {
        return(m_Data[row].Hgb);
    }

    else if (role == Ferritin)
    {
        return(m_Data[row].Ferritin);
    }

    else if (role == ESR)
    {
        return(m_Data[row].ESR);
    }

    else if (role == Na)
    {
        return(m_Data[row].Na);
    }

    else if (role == K)
    {
        return(m_Data[row].K);
    }

    else if (role == Mg)
    {
        return(m_Data[row].Mg);
    }

    else if (role == VitaminD)
    {
        return(m_Data[row].VitaminD);
    }

    else if (role == FBS)
    {
        return(m_Data[row].FBS);
    }

    else if (role == TG)
    {
        return(m_Data[row].TG);
    }

    else if (role == Cholestrol)
    {
        return(m_Data[row].Cholestrol);
    }

    else if (role == AST)
    {
        return(m_Data[row].AST);
    }

    else if (role == ALT)
    {
        return(m_Data[row].ALT);
    }

    else if (role == ALKPh)
    {
        return(m_Data[row].ALKPh);
    }

    else if (role == BUN)
    {
        return(m_Data[row].BUN);
    }

    else if (role == Cr)
    {
        return(m_Data[row].Cr);
    }

    else if (role == UA)
    {
        return(m_Data[row].UA);
    }

    else if (role == SE_OB)
    {
        return(m_Data[row].SE_OB);
    }
    else if (role == SE_OP)
    {
        return(m_Data[row].SE_OP);
    }

    else if (role == H_Pylori_Ab)
    {
        return(m_Data[row].H_Pylori_Ab);
    }

    else if (role == H_Pylori_Ag_SE)
    {
        return(m_Data[row].H_Pylori_Ag_SE);
    }

    else if (role == Tuberculin_test)
    {
        return(m_Data[row].Tuberculin_test);
    }

    else if (role == Pathergy_test)
    {
        return(m_Data[row].Pathergy_test);
    }

    else if (role == Sonography)
    {
        return(m_Data[row].Sonography);
    }

    else if (role == TSH)
    {
        return(m_Data[row].TSH);
    }

    else if (role == LH)
    {
        return(m_Data[row].LH);
    }

    else if (role == FSH)
    {
        return(m_Data[row].FSH);
    }

    else if (role == DHEAS)
    {
        return(m_Data[row].DHEAS);
    }

    else if (role == OH_P_17)
    {
        return(m_Data[row].OH_P_17);
    }

    else if (role == Prolactine)
    {
        return(m_Data[row].Prolactine);
    }

    else if (role == Testosterone)
    {
        return(m_Data[row].Testosterone);
    }

    else if (role == Hepatitis_Ag)
    {
        return(m_Data[row].Hepatitis_Ag);
    }

    else if (role == Hepatitis_Ab)
    {
        return(m_Data[row].Hepatitis_Ab);
    }

    else if (role == ANA)
    {
        return(m_Data[row].ANA);
    }

    else if (role == Anti_DS_Ab)
    {
        return(m_Data[row].Anti_DS_Ab);
    }

    else if (role == Anti_SCL70_Ab)
    {
        return(m_Data[row].Anti_SCL70_Ab);
    }

    else if (role == IgE)
    {
        return(m_Data[row].IgE);
    }

    return(QVariant());
}

QHash<int, QByteArray> PatientLabTestsModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { LabTestID, "labTestID" },
        { PatientID, "patientID" },
        { LabID, "labID" },
        { Date, "date" },
        { Outcome, "outcome" },
        { Name, "name" },
        { Specialization, "specialization" },
        { CBC, "CBC" },
        { WBC, "WBC" },
        { Hgb, "Hgb" },
        { Ferritin, "Ferritin" },
        { ESR, "ESR" },
        { Na, "Na" },
        { K, "K" },
        { Mg, "Mg" },
        { VitaminD, "VitaminD" },
        { FBS, "FBS" },
        { TG, "TG" },
        { Cholestrol, "Cholestrol" },
        { AST, "AST" },
        { ALT, "ALT" },
        { ALKPh, "ALKPh" },
        { BUN, "BUN" },
        { Cr, "Cr" },
        { UA, "UA" },
        { SE_OB, "SE_OB" },
        { SE_OP, "SE_OP" },
        { H_Pylori_Ab, "H_Pylori_Ab" },
        { H_Pylori_Ag_SE, "H_Pylori_Ag_SE" },
        { Tuberculin_test, "Tuberculin_test" },
        { Pathergy_test, "Pathergy_test" },
        { Sonography, "Sonography" },
        { TSH, "TSH" },
        { LH, "LH" },
        { FSH, "FSH" },
        { DHEAS, "DHEAS" },
        { OH_P_17, "OH_P_17" },
        { Prolactine, "Prolactine" },
        { Testosterone, "Testosterone" },
        { Hepatitis_Ag, "Hepatitis_Ag" },
        { Hepatitis_Ab, "Hepatitis_Ab" },
        { ANA, "ANA" },
        { Anti_DS_Ab, "Anti_DS_Ab" },
        { Anti_SCL70_Ab, "Anti_SCL70_Ab" },
        { IgE, "IgE" }
    };

    return(roleMapping);
}

bool PatientLabTestsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > m_Data.size() || row + count < 0 || row + count > m_Data.size())
    {
        return(false);
    }

    beginRemoveRows(parent, row, row + count - 1);

    m_Data.erase(
        m_Data.begin() + row,
        m_Data.begin() + row + count
    );

    endRemoveRows();

    return(true);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void PatientLabTestsModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingPatientLabTests,
        this,
        [this](int status, const QString& message, const std::vector<LabTest> data)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                setData(data);
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedInsertingPatientLabTest,
        this,
        [this](int status, const QString& message, LabTest labTest)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                const int index = m_Data.size();

                beginInsertRows(QModelIndex(), index, index);

                m_Data.emplace_back(
                    labTest.labTestID,
                    labTest.patientID,
                    labTest.labID,
                    labTest.date,
                    labTest.outcome,
                    labTest.name,
                    labTest.specialization,
                    labTest.CBC,
                    labTest.WBC,
                    labTest.Hgb,
                    labTest.Ferritin,
                    labTest.ESR,
                    labTest.Na,
                    labTest.K,
                    labTest.Mg,
                    labTest.VitaminD,
                    labTest.FBS,
                    labTest.TG,
                    labTest.Cholestrol,
                    labTest.AST,
                    labTest.ALT,
                    labTest.ALKPh,
                    labTest.BUN,
                    labTest.Cr,
                    labTest.UA,
                    labTest.SE_OB,
                    labTest.SE_OP,
                    labTest.H_Pylori_Ab,
                    labTest.H_Pylori_Ag_SE,
                    labTest.Tuberculin_test,
                    labTest.Pathergy_test,
                    labTest.Sonography,
                    labTest.TSH,
                    labTest.LH,
                    labTest.FSH,
                    labTest.DHEAS,
                    labTest.OH_P_17,
                    labTest.Prolactine,
                    labTest.Testosterone,
                    labTest.Hepatitis_Ag,
                    labTest.Hepatitis_Ab,
                    labTest.ANA,
                    labTest.Anti_DS_Ab,
                    labTest.Anti_SCL70_Ab,
                    labTest.IgE
                );

                endInsertRows();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedRemovingPatientLabTest,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                removeRows(m_Row, 1, QModelIndex());
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedUpdatingPatientLabTest,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                m_Data[m_Row] = m_LabTest;
            }

            // NOTE (SAVIZ): In this case, we're working with a one-dimensional list (i.e., only column 0), so it's safe to hardcode the column value. However, for tables with multiple columns, we should store the column index in a member variable and account for it accordingly.
            QModelIndex targetIndex = index(m_Row, 0);

            emit dataChanged(targetIndex, targetIndex, {   LabTestID,
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
                                                           IgE });

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    emit databaseChanged();
}

void PatientLabTestsModel::setData(std::vector<LabTest> newData)
{
    beginResetModel();

    m_Data = newData;

    endResetModel();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Getters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Database *PatientLabTestsModel::getDatabase() const
{
    return(m_Database);
}

bool PatientLabTestsModel::getOperationIsInProgress() const
{
    return(m_OperationIsInProgress);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
