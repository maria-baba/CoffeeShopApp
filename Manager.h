//
// Created by surug on 1/7/2025.
//

#ifndef MANAGER_H
#define MANAGER_H

#include "Angajat.h"
#include "EvenimenteSpeciale.h"

// MOSTENIRE
class Manager : public Angajat {
public:
    Manager(const string& nume, double salariuPeOra, const vector<string>& tura);
    void afiseazaDetalii() const override;

    static void adaugaAngajat(const string& filePath, const string& nume, const string& functie, double salariuPeOra, const vector<string>& tura);
    static void stergeAngajat(const string& filePath, const string& nume);
    static void schimbaTura(const string& filePath, const string& nume, const vector<string>& turaNoua);

    static double calculVenituriProduse(const string& filePathComenzi);
    static double calculCostProduse(const string& filePathProduse);
    static double salariuAngajatiPeZi(const string& filePathAngajati, const string& zi);

    static void adaugaEvenimentSpecial(const string& filePath, const EvenimenteSpeciale& eveniment);
    static void stergeEvenimentSpecial(const string& filePath, const string& numeEveniment);

    static void genereazaRaportFinal(const string& filePathComenzi, const string& filePathProduse,
                                      const string& filePathAngajati, const string& filePathEvenimente,
                                      const string& filePathRaport, const string& dataCurenta, const string& zi);
};


#endif //MANAGER_H
