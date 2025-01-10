//
// Created by surug on 1/3/2025.
//

#ifndef PRODUS_H
#define PRODUS_H

#include <string>
#include <iostream>

using namespace std;

class Produs {
private:
    string nume;
    double pret_vanzare;
    double pret_achizitie;
    int unitati_in_stoc;

public:
    Produs();
    // Constructor cu parametri
    Produs(const string& nume, double pret_vanzare, double pret_achizitie, int unitati_in_stoc);

    // Getters
    string getNume() const;
    double getPretVanzare() const;
    double getPretAchizitie() const;
    int getUnitatiInStoc() const;

    // Setter pentru unitati_in_stoc
    void setUnitatiInStoc(int stocNou);

    static bool existaProdus(const string& filePath, const string& numeProdus);

    friend istream& operator>>(istream& is, Produs& produs);
    friend ostream& operator<<(ostream& os, const Produs& produs);

};

#endif // PRODUS_H
