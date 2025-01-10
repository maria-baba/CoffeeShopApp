//
// Created by surug on 1/4/2025.
//

#ifndef COMANDA_H
#define COMANDA_H

#include "Produs.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Comanda {
private:
    string nume_client;
    vector<string> produse;
    double pret_total;

public:
    Comanda();

    Comanda(const string& nume_client, const vector<string>& produse, double pret_total);

    void adaugaComanda(const string& filePathProduse, const string& filePathComenzi, const string& filePathClienti);

    double calculeazaPretTotal(const vector<string>& produse_comandate, const vector<Produs>& produse_disponibile) const;

    const string& getNumeClient() const;
    const vector<string>& getProduse() const;
    double getPretTotal() const;

    friend ostream& operator<<(ostream& os, const Comanda& comanda);

};

#endif // COMANDA_H
