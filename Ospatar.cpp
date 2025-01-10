//
// Created by surug on 1/7/2025.
//

#include "Ospatar.h"
#include <iostream>

Ospatar::Ospatar(const string& nume, double salariuPeOra, const vector<string>& tura)
    : Angajat(nume, "ospatar", salariuPeOra, tura) {}

void Ospatar::afiseazaDetalii() const {
    Angajat::afiseazaDetalii();
    cout << "Rol: Ospatar.\n";
}