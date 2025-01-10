//
// Created by surug on 1/7/2025.
//

#include "Barista.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Barista::Barista(const string& nume, double salariuPeOra, const vector<string>& tura)
    : Angajat(nume, "barista", salariuPeOra, tura) {}

void Barista::afiseazaDetalii() const {
    Angajat::afiseazaDetalii();
    cout << "Rol: Barista.\n";
}

void Barista::reinoiesteStoc(const string& filePath, const string& produsEpuizat) {
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cerr << "Nu s-a putut deschide fișierul pentru citire: " << filePath << endl;
        return;
    }

    vector<string> linii;
    string linie;
    bool produsGasit = false;

    while (getline(inFile, linie)) {
        stringstream ss(linie);
        string numeProdus;
        getline(ss, numeProdus, ',');

        if (numeProdus == produsEpuizat) {
            produsGasit = true;
            string pretVanzare, pretAchizitie, unitatiInStoc;
            getline(ss, pretVanzare, ',');
            getline(ss, pretAchizitie, ',');
            getline(ss, unitatiInStoc, ',');

            // Actualizează stocul
            int stocNou = 20;
            linii.push_back(numeProdus + "," + pretVanzare + "," + pretAchizitie + "," + to_string(stocNou));
        } else {
            linii.push_back(linie);
        }
    }

    inFile.close();

    if (!produsGasit) {
        cerr << "Produsul " << produsEpuizat << " nu a fost gasit în fisier.\n";
        return;
    }

    // modifica fisierul
    ofstream outFile(filePath);
    if (!outFile.is_open()) {
        cerr << "Nu s-a putut deschide fisierul pentru scriere: " << filePath << endl;
        return;
    }

    for (const auto& linieActualizata : linii) {
        outFile << linieActualizata << "\n";
    }

    outFile.close();
    cout << "Stocul pentru produsul " << produsEpuizat << " a fost reinnoit cu 20 de unitati.\n";
}
