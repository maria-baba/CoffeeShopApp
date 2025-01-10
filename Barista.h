//
// Created by surug on 1/7/2025.
//

#ifndef BARISTA_H
#define BARISTA_H

#include "Angajat.h"

// MOSTENIRE
class Barista : public Angajat {
public:
    Barista(const string& nume, double salariuPeOra, const vector<string>& tura);
    void afiseazaDetalii() const override;
    static void reinoiesteStoc(const string& filePath, const string& produsEpuizat);
};




#endif //BARISTA_H
