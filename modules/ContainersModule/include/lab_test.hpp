#ifndef LABTEST_H
#define LABTEST_H

#include <QString>

// NOTE (SAVIZ): I really want the 'QString' types to be 'const QString &' types
// instead here, but I cannot figure out how to do it without getting a lot of
// errors regarding initial value.

struct LabTest {
public:
    LabTest() = default;
    LabTest(const int labTestID, const int patientID, const int labID,
            const QString &date, const QString &outcome, const QString &name,
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
            const int igE);
    ~LabTest() = default;

    int labTestID;
    int patientID;
    int labID;
    QString date;
    QString outcome;
    QString name;
    QString specialization;
    int CBC;
    int WBC;
    int Hgb;
    int Ferritin;
    int ESR;
    int Na;
    int K;
    int Mg;
    int VitaminD;
    int FBS;
    int TG;
    int Cholestrol;
    int AST;
    int ALT;
    int ALKPh;
    int BUN;
    int Cr;
    int UA;
    int SE_OB;
    int SE_OP;
    int H_Pylori_Ab;
    int H_Pylori_Ag_SE;
    int Tuberculin_test;
    int Pathergy_test;
    int Sonography;
    int TSH;
    int LH;
    int FSH;
    int DHEAS;
    int OH_P_17; // variable name connot start with a number.
    int Prolactine;
    int Testosterone;
    int Hepatitis_Ag;
    int Hepatitis_Ab;
    int ANA;
    int Anti_DS_Ab;
    int Anti_SCL70_Ab;
    int IgE;
};

#endif // LabTest_H
