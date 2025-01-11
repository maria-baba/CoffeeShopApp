//
// Created by surug on 1/7/2025.
//

#include "Manager.h"
#include "CSVHandler.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

Manager::Manager(const string& nume, double salariuPeOra, const vector<string>& tura)
    : Angajat(nume, "manager", salariuPeOra, tura) {}

void Manager::afiseazaDetalii() const {
    Angajat::afiseazaDetalii();
    cout << "Rol: Manager.\n";
}

void Manager::adaugaAngajat(const string& filePath, const string& numeNou, const string& functieNoua, double salariuNou, const vector<string>& turaNoua) {
    vector<Angajat*> angajati = CSVHandler::citesteAngajati(filePath);

    Angajat* angajatNou;
    if (functieNoua == "manager") {
        angajatNou = new Manager(numeNou, salariuNou, turaNoua);
    } else if (functieNoua == "barista") {
        angajatNou = new Barista(numeNou, salariuNou, turaNoua);
    } else if (functieNoua == "ospatar") {
        angajatNou = new Ospatar(numeNou, salariuNou, turaNoua);
    } else {
        cout << "Functia specificata nu este valida.\n";
        return;
    }

    angajati.push_back(angajatNou);

    CSVHandler::scrieAngajati(filePath, angajati);

    cout << "Angajat adaugat cu succes.\n";
}
void Manager::stergeAngajat(const string& filePath, const string& numeAngajat) {
    vector<Angajat*> angajati = CSVHandler::citesteAngajati(filePath);

    // remove_if pentru a elimina angajatul
    auto it = remove_if(angajati.begin(), angajati.end(),
        [&numeAngajat](Angajat* angajat) {
            return angajat->getNume() == numeAngajat;
        });

    if (it != angajati.end()) {
        angajati.erase(it, angajati.end());
        cout << "Angajatul a fost sters.\n";
    } else {
        cout << "Angajatul nu a fost gasit.\n";
    }

    CSVHandler::scrieAngajati(filePath, angajati);

    // free memory
    for (Angajat* angajat : angajati) {
        delete angajat;
    }
}
void Manager::schimbaTura(const string& filePath, const string& numeAngajat, const vector<string>& turaNoua) {
    vector<Angajat*> angajati = CSVHandler::citesteAngajati(filePath);
    bool gasit = false;

    for (auto& angajat : angajati) {
        if (angajat->getNume() == numeAngajat) {
            gasit = true;

            // Modifica tura
            angajat->setTura(turaNoua);
            break;
        }
    }

    if (gasit) {
        CSVHandler::scrieAngajati(filePath, angajati);
        cout << "Tura modificata cu succes.\n";
    } else {
        cout << "Angajatul nu a fost gasit.\n";
    }

    // free memory
    for (auto& angajat : angajati) {
        delete angajat;
    }
}

// functii pt raport final
double Manager::calculVenituriProduse(const string& filePathComenzi) {
    ifstream file(filePathComenzi);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului comenzi.csv!\n";
        return 0.0;
    }

    string linie;
    double venituriTotale = 0.0;

    // (antetul)
    getline(file, linie);

    while (getline(file, linie)) {
        stringstream ss(linie);
        string element;

        // Extragem pret total
        getline(ss, element, ','); // Primul camp (nume client) - ignorat
        getline(ss, element, ','); // Al doilea câmp (pret total)

        cout << "Pret total: " << element << "\n";
        try {
            double pretTotal = stod(element); // conversia în double
            venituriTotale += pretTotal;
        } catch (const invalid_argument& e) {
            cerr << "Eroare la conversia pretului total: " << element << "\n";
        } catch (const out_of_range& e) {
            cerr << "Pret total prea mare pentru conversie: " << element << "\n";
        }
    }

    file.close();
    return venituriTotale;
}
double Manager::calculCostProduse(const string &filePathProduse) {
    vector <Produs> produse = CSVHandler::citesteProduse(filePathProduse);
    double costTotal = 0.0;

    for(auto& produs : produse) {
        costTotal += produs.getPretAchizitie() * produs.getUnitatiInStoc();

        if(produs.getUnitatiInStoc() == 0) {
            costTotal += 20 * produs.getPretAchizitie();
            produs.setUnitatiInStoc(20);
        }
    }

    CSVHandler::scrieProduse(filePathProduse, produse);
    cout << "Costul total al produselor este: " << costTotal << " lei.\n";

    return costTotal;
}
double Manager::salariuAngajatiPeZi(const string& filePath, const string& zi) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul.");
    }

    string line;
    double totalSalariu = 0;

    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        string nume, functie;
        double salariuPeOra;

        getline(ss, nume, ',');
        getline(ss, functie, ',');
        ss >> salariuPeOra;

        ss.ignore();

        while (ss.good()) {
            string ziLucru;
            getline(ss, ziLucru, ',');
            if (ziLucru.empty()) break;

            string interval;
            getline(ss, interval, ',');

            if (ziLucru == zi) {
                int startHour = stoi(interval.substr(0, 2));
                int endHour = stoi(interval.substr(3, 2));
                int oreLucrate = endHour - startHour;
                totalSalariu += oreLucrate * salariuPeOra;
            }
        }
    }

    file.close();
    return totalSalariu;
}

void Manager::adaugaEvenimentSpecial(const string& filePathEvenimente, const EvenimenteSpeciale& eveniment) {
    CSVHandler::adaugaEveniment(filePathEvenimente, eveniment);
    cout << "Eveniment special adaugat cu succes.\n";
}
void Manager::stergeEvenimentSpecial(const string& filePathEvenimente, const string& numeEveniment) {
    vector<EvenimenteSpeciale> evenimente = CSVHandler::citesteEvenimente(filePathEvenimente);

    auto it = remove_if(evenimente.begin(), evenimente.end(),
        [&numeEveniment](const EvenimenteSpeciale& eveniment) {
            return eveniment.getNumeEveniment() == numeEveniment;
        });

    if (it != evenimente.end()) {
        evenimente.erase(it, evenimente.end());
        cout << "Evenimentul a fost sters.\n";
    } else {
        cout << "Evenimentul nu a fost gasit.\n";
    }

    CSVHandler::scrieEvenimente(filePathEvenimente, evenimente);
}
void Manager::genereazaRaportFinal(const string& filePathComenzi, const string& filePathProduse,
                                     const string& filePathAngajati, const string& filePathEvenimente,
                                     const string& filePathRaport, const string& dataCurenta, const string& zi) {
    // folosim functiile deja definite pentru a calcula veniturile, costurile si salariile
    double venituriProduse = calculVenituriProduse(filePathComenzi);
    double costuriProduse = calculCostProduse(filePathProduse);
    double salarii = salariuAngajatiPeZi(filePathAngajati, zi);

    double venituriEvenimente = 0.0;
    double cheltuieliEvenimente = 0.0;

    ifstream fisierEvenimente(filePathEvenimente);
    if (!fisierEvenimente.is_open()) {
        cerr << "Eroare la deschiderea fisierului cu evenimente: " << filePathEvenimente << endl;
        return;
    }

    string linie;
    // antetul
    getline(fisierEvenimente, linie);

    while (getline(fisierEvenimente, linie)) {
        stringstream ss(linie);
        string dataEveniment, numeEveniment;
        double costEveniment;

        getline(ss, dataEveniment, ',');
        getline(ss, numeEveniment, ',');
        ss >> costEveniment;

        if (dataEveniment == dataCurenta) {
            // consider ca venituriEvenimente sunt egale cu venituriProduse(daca in ziua respectiva a avut loc un eveniment)
            venituriEvenimente += venituriProduse;
            cheltuieliEvenimente += costEveniment;
        }
    }

    fisierEvenimente.close();

    double profit = venituriProduse - (costuriProduse + salarii + cheltuieliEvenimente);

    cout << fixed << setprecision(2);
    cout << "Data: " << dataCurenta << endl;
    cout << "Venituri Produse: " << venituriProduse << " lei" << endl;
    cout << "Costuri Produse: " << costuriProduse << " lei" << endl;
    cout << "Salarii: " << salarii << " lei" << endl;
    cout << "Venituri Evenimente: " << venituriEvenimente << " lei" << endl;
    cout << "Cheltuieli Evenimente: " << cheltuieliEvenimente << " lei" << endl;
    cout << "Profit: " << profit << " lei" << endl;

    ofstream fisierRaport(filePathRaport, ios::app); // Open in append mode
    if (!fisierRaport.is_open()) {
        cerr << "Eroare la deschiderea fisierului pentru raport." << endl;
        return;
    }

    fisierRaport << fixed << setprecision(2);
    fisierRaport << dataCurenta << ","
                 << venituriProduse << ","
                 << costuriProduse << ","
                 << salarii << ","
                 << venituriEvenimente << ","
                 << cheltuieliEvenimente << ","
                 << profit << "\n";

    fisierRaport.close();
}