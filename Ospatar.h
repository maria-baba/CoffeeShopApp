//
// Created by surug on 1/7/2025.
//

#ifndef OSPATAR_H
#define OSPATAR_H

#include "Angajat.h"

// MOSTENIRE
class Ospatar : public Angajat {
public:
    Ospatar(const string& nume, double salariuPeOra, const vector<string>& tura);
    void afiseazaDetalii() const override;
};

#endif //OSPATAR_H
