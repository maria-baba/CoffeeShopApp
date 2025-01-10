//
// Created by surug on 1/3/2025.
//

#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Angajat {
protected:
    string nume;
    string functie;
    double salariuPeOra;
    vector<string> tura;

public:
    Angajat();
    Angajat(const string& nume, const string& functie, double salariuPeOra, const vector<string>& tura);
    virtual ~Angajat() = default;

    string getNume() const;
    string getFunctie() const;
    double getSalariuPeOra() const;
    const vector<string>& getTura() const;
    void setTura(const vector<string>& turaNoua);

    virtual void afiseazaDetalii() const;

    friend ostream& operator<<(ostream& os, const Angajat& angajat);
    friend istream& operator>>(istream& is, Angajat& angajat);
};

#endif // ANGAJAT_H