#include "lab_test.hpp"
#include <QDebug>

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

LabTest::LabTest(const int labTestID, const int patientID,
                 const int labID, const QString &date,
                 const QString &outcome, const QString &name,
                 const QString &specialization,
                 const int cBC,
                 const int wBC,
                 const int hgb,
                 const int ferritin,
                 const int eSR,
                 const int na,
                 const int k,
                 const int mg,
                 const int vitaminD,
                 const int fBS,
                 const int tG,
                 const int cholestrol,
                 const int aST,
                 const int aLT,
                 const int aLKPh,
                 const int bUN,
                 const int cr,
                 const int uA,
                 const int sE_OB,
                 const int sE_OP,
                 const int h_Pylori_Ab,
                 const int h_Pylori_Ag_SE,
                 const int tuberculin_test,
                 const int pathergy_test,
                 const int sonography,
                 const int tSH,
                 const int lH,
                 const int fSH,
                 const int dHEAS,
                 const int oH_P_17,
                 const int prolactine,
                 const int testosterone,
                 const int hepatitis_Ag,
                 const int hepatitis_Ab,
                 const int aNA,
                 const int anti_DS_Ab,
                 const int anti_SCL70_Ab,
                 const int igE)
    : labTestID(labTestID), patientID(patientID), labID(labID),
    date(date), outcome(outcome), name(name), specialization(specialization)
    , CBC (cBC)
    , WBC (wBC)
    , Hgb (hgb)
    , Ferritin (ferritin)
    , ESR (eSR)
    , Na (na)
    , K (k)
    , Mg (mg)
    , VitaminD (vitaminD)
    , FBS (fBS)
    , TG (tG)
    , Cholestrol (cholestrol)
    , AST (aST)
    , ALT (aLT)
    , ALKPh (aLKPh)
    , BUN (bUN)
    , Cr (cr)
    , UA (uA)
    , SE_OB (sE_OB)
    , SE_OP (sE_OP)
    , H_Pylori_Ab (h_Pylori_Ab)
    , H_Pylori_Ag_SE (h_Pylori_Ag_SE)
    , Tuberculin_test (tuberculin_test)
    , Pathergy_test (pathergy_test)
    , Sonography (sonography)
    , TSH (tSH)
    , LH (lH)
    , FSH (fSH)
    , DHEAS (dHEAS)
    , OH_P_17 (oH_P_17)
    , Prolactine (prolactine)
    , Testosterone (testosterone)
    , Hepatitis_Ag (hepatitis_Ag)
    , Hepatitis_Ab (hepatitis_Ab)
    , ANA (aNA)
    , Anti_DS_Ab (anti_DS_Ab)
    , Anti_SCL70_Ab (anti_SCL70_Ab)
    , IgE (igE)
{

}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
