//
// Created by surug on 1/9/2025.
//

#include "Client.h"
#include "CSVHandler.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Client::Client(const std::string& nume, double total_cheltuit, int numar_comenzi, double reducere)
    : nume(nume), total_cheltuit(total_cheltuit), numar_comenzi(numar_comenzi), reducere(reducere) {}

const string& Client::getNume() const {
    return nume;
}
double Client::getTotalCheltuit() const {
    return total_cheltuit;
}
int Client::getNumarComenzi() const {
    return numar_comenzi;
}
double Client::getReducere() const {
    return reducere;
}

void Client::setTotalCheltuit(double total) {
    total_cheltuit = total;
}
void Client::setNumarComenzi(int numar) {
    numar_comenzi = numar;
}
void Client::setReducere(double reducere) {
    this->reducere = reducere;
}

double Client::proceseazaClient(const string& filePathClienti, const string& nume_client, double total_achizitie_curent) {
    vector<Client> clienti = CSVHandler::citesteClienti(filePathClienti);
    bool client_gasit = false;
    double reducere = 0.0;
    double pret_final = total_achizitie_curent;

    for (auto& client : clienti) {
        if (client.getNume() == nume_client) {
            client_gasit = true;

            // incrementam nr comenzi, actualizam totalul cheltuit
            client.setNumarComenzi(client.getNumarComenzi() + 1);
            client.setTotalCheltuit(client.getTotalCheltuit() + total_achizitie_curent);

            // calculare reducerea
            if (client.getNumarComenzi() % 5 == 0) {
                reducere = 0.15 * total_achizitie_curent; // Reducere de 15%
                client.setReducere(max(client.getReducere(), reducere*client.getNumarComenzi()/5));
                cout << "\n" << client.getNume() << " beneficiezi de o reducere de: " << reducere << " pentru 5 comenzi!\n";

            }

            break;
        }
    }

    // dacă clientul nu a fost gasit, adaugam unul nou
    if (!client_gasit) {
        Client client_nou(nume_client, total_achizitie_curent, 1, 0);
        clienti.push_back(client_nou);
    }

    CSVHandler::scrieClienti(filePathClienti, clienti);

    return reducere;
}


