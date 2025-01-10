//
// Created by surug on 1/9/2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Client {
private:
    string nume;
    double total_cheltuit;
    int numar_comenzi;
    double reducere;
public:
    // Constructori
    Client(const std::string& nume, double total_cheltuit, int numar_comenzi, double reducere);

    // Getteri și setteri
    const string& getNume() const;
    double getTotalCheltuit() const;
    int getNumarComenzi() const;
    double getReducere() const;


    void setTotalCheltuit(double total);
    void setNumarComenzi(int numar);
    void setReducere(double reducere);

    // Funcție pentru procesarea comenzilor și actualizarea datelor clientului
    static double proceseazaClient(const string& filePathClienti, const string& nume_client, double total_achizitie_curent);

};
#endif // CLIENT_H
