//
// Created by surug on 1/4/2025.
//

#include "Comanda.h"
#include "CSVHandler.h"
#include "Produs.h"
#include "Barista.h"
#include <map>
#include <sstream>
#include <limits>
#include <iomanip>

Comanda::Comanda() : nume_client(""), produse({}), pret_total(0.0) {}

Comanda::Comanda(const string &nume_client, const vector<string> &produse, double pret_total)
    : nume_client(nume_client), produse(produse), pret_total(pret_total) {}

void Comanda::adaugaComanda(const string& filePathProduse, const string& filePathComenzi, const string& filePathClienti) {
    string nume_client;
    vector<string> produse_comandate;

    cout << "Introdu numele clientului:\n";
    cin.ignore();
    getline(cin, nume_client);

    vector<Produs> produse_disponibile = CSVHandler::citesteProduse(filePathProduse);

    string nume_produs;
    while (true) {
        cout << "Introdu un produs (sau 'gata' pentru a finaliza comanda):\n";
        getline(cin, nume_produs);

        if (nume_produs == "gata") break;

        auto it = find_if(produse_disponibile.begin(), produse_disponibile.end(),
                          [&nume_produs](const Produs& p) { return p.getNume() == nume_produs; });

        if (it != produse_disponibile.end()) {
            if (it->getUnitatiInStoc() > 0) {
                produse_comandate.push_back(nume_produs);
                it->setUnitatiInStoc(it->getUnitatiInStoc() - 1);
            } else if (it->getUnitatiInStoc() == 0) {
                // Produsul nu este în stoc - reînnoiește stocul
                cout << "Produsul " << nume_produs << " nu mai este in stoc!\n";
                cout << "Asteptati...stocul va fi reinnoit de barista noastra!\n";

                Barista::reinoiesteStoc(filePathProduse, nume_produs);

                // reciteste stocul actualizat
                produse_disponibile = CSVHandler::citesteProduse(filePathProduse);

                // gaseste din nou produsul in lista actualizata
                it = find_if(produse_disponibile.begin(), produse_disponibile.end(),
                             [&nume_produs](const Produs& p) { return p.getNume() == nume_produs; });

                if (it != produse_disponibile.end() && it->getUnitatiInStoc() > 0) {
                    produse_comandate.push_back(nume_produs);
                    it->setUnitatiInStoc(it->getUnitatiInStoc() - 1);
                } else {
                    cout << "Eroare: Stocul pentru " << nume_produs << " nu a fost reinnoit corect.\n";
                }
            }
        } else {
            cout << "Produsul " << nume_produs << " nu exista! Alegeti altceva, va rugam.\n";
        }
    }

    if (!produse_comandate.empty()) {
        // aplica reducerea clientului
        pret_total = calculeazaPretTotal(produse_comandate, produse_disponibile);
        double reducere_aplicata = Client::proceseazaClient(filePathClienti, nume_client, pret_total);
        double pret_actualizat = pret_total - reducere_aplicata;

        CSVHandler::scrieComanda(filePathComenzi, nume_client, produse_comandate, pret_actualizat);
        CSVHandler::scrieProduse(filePathProduse, produse_disponibile);

        cout << "Comanda adaugata cu succes.\n";
        cout << "Pretul total va fi de: " << pret_actualizat << " lei.\n";
        cout << "Multumim pentru comanda!\n";
    } else {
        cout << "Nu s-a adaugat nicio comanda.\n";
    }
}
double Comanda::calculeazaPretTotal(const vector<string>& produse_comandate, const vector<Produs>& produse_disponibile) const {
    double pret_total = 0.0;
    for (const auto& nume_produs : produse_comandate) {
        auto it = find_if(produse_disponibile.begin(), produse_disponibile.end(),
                          [&nume_produs](const Produs& p) { return p.getNume() == nume_produs; });
        if (it != produse_disponibile.end()) {
            pret_total += it->getPretVanzare();
        }
    }
    return pret_total;
}

const string& Comanda::getNumeClient() const {
    return nume_client;
}
const vector<string>& Comanda::getProduse() const {
    return produse;
}
double Comanda::getPretTotal() const {
    return pret_total;
}

ostream& operator<<(ostream& os, const Comanda& comanda) {
    os << left; // Align text to the left
    os << setw(20) << "Client:" << comanda.getNumeClient() << "\n"; // Set width for Client
    os << setw(20) << "Produse comandate:";

    // Iterate through products and print them in a formatted manner
    const auto& produse = comanda.getProduse();
    for (size_t i = 0; i < produse.size(); ++i) {
        os << produse[i];
        if (i < produse.size() - 1) {
            os << ", "; // Add a comma if it's not the last product
        }
    }

    os << "\n" << setw(20) << "Pret total:" << comanda.getPretTotal() << " lei\n";
    return os;
}
