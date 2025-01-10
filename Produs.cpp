//
// Created by surug on 1/3/2025.
//

#include "Produs.h"
#include <fstream>
#include <sstream>

Produs::Produs() : pret_vanzare(0), pret_achizitie(0), unitati_in_stoc(0) {}

// Constructor cu parametri
Produs::Produs(const string& nume, double pret_vanzare, double pret_achizitie, int unitati_in_stoc)
    : nume(nume), pret_vanzare(pret_vanzare), pret_achizitie(pret_achizitie), unitati_in_stoc(unitati_in_stoc) {}

// Getters
string Produs::getNume() const { return nume; }
double Produs::getPretVanzare() const { return pret_vanzare; }
double Produs::getPretAchizitie() const { return pret_achizitie; }
int Produs::getUnitatiInStoc() const { return unitati_in_stoc; }

void Produs::setUnitatiInStoc(int stocNou) { unitati_in_stoc = stocNou; }

bool Produs::existaProdus(const string& filePath, const string& numeProdus) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului produse.csv!\n";
        return false;
    }

    string linie;
    getline(file, linie); // Sărim peste antet

    while (getline(file, linie)) {
        stringstream ss(linie);
        string nume;
        getline(ss, nume, ',');
        if (nume == numeProdus) {
            return true; // Produsul există
        }
    }

    file.close();
    return false; // Produsul nu există
}

// Suprascrierea operatorului >>
istream& operator>>(istream& is, Produs& produs) {
    cout << "Introdu numele produsului:\n";
    is.ignore();
    getline(is, produs.nume);
    cout << "Introdu pretul de achizitie:\n";
    is >> produs.pret_achizitie;
    cout << "Introdu pretul de vanzare:\n";
    is >> produs.pret_vanzare;
    cout << "Introdu unitatile in stoc:\n";
    is >> produs.unitati_in_stoc;
    return is;
}
// Suprascrierea operatorului <<
ostream& operator<<(ostream& os, const Produs& produs) {
    os << "Nume: " << produs.getNume()
       << ", Pret vanzare: " << produs.getPretVanzare()
       << ", Pret achizitie: " << produs.getPretAchizitie()
       << ", Unitati in stoc: " << produs.getUnitatiInStoc();
    return os;
}

