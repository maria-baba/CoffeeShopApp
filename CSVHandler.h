//
// Created by surug on 1/3/2025.
//

#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <algorithm>
#include <fstream> // pentru ifstream, ofstream
#include <iostream>
#include <map>
#include <sstream> // pentru stringstream
#include <vector>
#include "Angajat.h"
#include "Barista.h"
#include "Client.h"
#include "Comanda.h"
#include "EvenimenteSpeciale.h"
#include "Manager.h"
#include "Ospatar.h"
#include "Produs.h"


using namespace std;

class CSVHandler {
public:
    // produse
    static vector<Produs> citesteProduse(const string& filePath);
    static void scrieProduse(const string& filePath, const vector<Produs>& produse);
    static void stergeProdus(const string& filePath, vector<Produs>& produse);

    // angajati
    static vector<Angajat*> citesteAngajati(const string& filePath);
    static void scrieAngajati(const string& filePath, const vector<Angajat*>& angajati);

    // comenzi
    static std::map<std::string, double> citestePreturiProduse(const string& cale);
    static void scrieComanda(const string& cale, const string& nume_client, const vector<string>& produse, double pret_total);
    static vector<Comanda> citesteComenzi(const string& cale);
    static void afiseazaComenzi(const vector<Comanda>& comenzi);

    // clienti
    static vector<Client> citesteClienti(const string& filePathClienti);
    static void scrieClienti(const string& filePathClienti, const vector<Client>& clienti);

    // evenimente speciale
    static vector<EvenimenteSpeciale> citesteEvenimente(const string& filePathEvenimente);
    static void scrieEvenimente(const string& filePathEvenimente, const vector<EvenimenteSpeciale>& evenimente);
    static void adaugaEveniment(const string& filePathEvenimente, const EvenimenteSpeciale& eveniment);

};

#endif //CSVHANDLER_H
