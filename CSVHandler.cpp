//
// Created by surug on 1/3/2025.
//

#include "CSVHandler.h"

// PRODUSE
vector<Produs> CSVHandler::citesteProduse(const string& filePath) {
    vector<Produs> produse;
    // Deschidem fisierul pentru citire
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului: " << filePath << endl;
        return produse;
    }

    string line;
    // Ignoram primul rand (antetul)
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string nume, pret_vanzare, pret_achizitie, stoc;

        getline(ss, nume, ',');
        getline(ss, pret_vanzare, ',');
        getline(ss, pret_achizitie, ',');
        getline(ss, stoc, ',');

        try {
            // Conversia datelor din string la tipurile corespunzatoare
            double pretVanzare = stof(pret_vanzare);
            double pretAchizitie = stof(pret_achizitie);
            int unitatiInStoc = stoi(stoc);

            // Adaugam produsul la vector
            produse.emplace_back(nume, pretVanzare, pretAchizitie, unitatiInStoc);
        } catch (const invalid_argument& e) {
            cerr << "Eroare la conversia datelor pentru produsul: " << nume << endl;
            cerr << "Detalii: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cerr << "Valoare prea mare pentru produsul: " << nume << endl;
            cerr << "Detalii: " << e.what() << endl;
        }
    }

    file.close();
    return produse;
}
void CSVHandler::scrieProduse(const string& filePath, const vector<Produs>& produse) {
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "Eroare la scrierea fisierului: " << filePath << endl;
        return;
    }

    // Scriem antetul
    file << "nume,pret vanzare,pret achizitie,unitati in stoc\n";
    for (const auto& produs : produse) {
        // Scriem datele produsului în format CSV
        file << produs.getNume() << ","
             << produs.getPretVanzare() << ","
             << produs.getPretAchizitie() << ","
             << produs.getUnitatiInStoc() << "\n";
    }

    file.close();
}
void CSVHandler::stergeProdus(const string& filePath, vector<Produs>& produse) {
    string numeProdus;
    cout << "Introdu numele produsului de sters:\n";
    cin.ignore();
    getline(cin, numeProdus);

    // Folosim remove_if pentru a gasi produsele care corespund numelui dat
    auto it = remove_if(produse.begin(), produse.end(),
                        [&numeProdus](const Produs& p) {
                            return p.getNume() == numeProdus;
                        });

    if (it != produse.end()) {
        produse.erase(it, produse.end());
        cout << "Produs sters cu succes.\n";
        scrieProduse(filePath, produse);
    } else {
        cout << "Produsul nu a fost gasit.\n";
    }
}

// ANGAJATI
vector<Angajat*> CSVHandler::citesteAngajati(const string& filePath) {
    vector<Angajat*> angajati;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Nu s-a putut deschide fisierul: " << filePath << endl;
        return angajati;
    }

    string linie;
    while (getline(file, linie)) {
        stringstream ss(linie);
        string nume, functie;
        double salariu;
        vector<string> tura;

        getline(ss, nume, ',');
        getline(ss, functie, ',');
        ss >> salariu;
        ss.ignore();

        // Citirea turelor
        string ziInterval;
        while (getline(ss, ziInterval, ',')) {
            tura.push_back(ziInterval);
        }

        // Crearea obiectelor Angajat pe baza funcției
        if (functie == "manager") {
            angajati.push_back(new Manager(nume, salariu, tura));
        } else if (functie == "barista") {
            angajati.push_back(new Barista(nume, salariu, tura));
        } else if (functie == "ospatar") {
            angajati.push_back(new Ospatar(nume, salariu, tura));
        }
    }

    file.close();
    return angajati;
}
void CSVHandler::scrieAngajati(const string& filePath, const vector<Angajat*>& angajati) {
    ofstream file(filePath);

    if (!file.is_open()) {
        cerr << "Nu s-a putut deschide fisierul pentru scriere: " << filePath << endl;
        return;
    }

    // Scriem antetul
    file << "nume,functie,salariu per ora,tura\n";

    for (const auto& angajat : angajati) {
        file << angajat->getNume() << ","
             << angajat->getFunctie() << ","
             << angajat->getSalariuPeOra();

        const vector<string>& tura = angajat->getTura();

        // Scriem turele în perechi de zi si interval orar
        for (size_t i = 0; i < tura.size(); i += 2) {
            if (i + 1 < tura.size()) { // Verificam ca exista un interval orar pentru ziua respectiva
                file << "," << tura[i] << "," << tura[i + 1]; // Scriem ziua si intervalul orar
            }
        }

        file << "\n";
    }

    file.close();
}

// COMENZI
map<string, double> CSVHandler::citestePreturiProduse(const string& cale) {
    map<string, double> preturi;
    ifstream fisier(cale);
    string linie;

    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fisierul: " << cale << endl;
        return preturi;
    }

    while (getline(fisier, linie)) {
        stringstream ss(linie);
        string nume_produs;
        double pret;

        getline(ss, nume_produs, ',');
        ss >> pret;

        preturi[nume_produs] = pret;
    }

    return preturi;
}
void CSVHandler::scrieComanda(const string& cale, const string& nume_client, const vector<string>& produse, double pret_total) {
    ofstream fisier(cale, ios::app);
    if (fisier.is_open()) {
        fisier << nume_client << "," << pret_total;
        for (const auto& produs : produse) {
            fisier << "," << produs;
        }
        fisier << "\n";
    } else {
        cerr << "Nu s-a putut deschide fisierul pentru scriere: " << cale << endl;
    }
}
vector<Comanda> CSVHandler::citesteComenzi(const string& cale) {
    vector<Comanda> comenzi;
    ifstream fisier(cale);
    string linie;

    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fisierul: " << cale << endl;
        return comenzi;
    }

    // Ignorăm primul rând (antetul)
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        stringstream ss(linie);
        string nume_client;
        double pret_total;
        vector<string> produse;
        string produs;

        getline(ss, nume_client, ',');

        // pret
        if (!(ss >> pret_total)) {
            cerr << "Eroare la citirea pretului total: " << linie << endl;
            continue;
        }

        ss.ignore(); // Ignoram virgula dupa pret

        // citim produsele
        while (getline(ss, produs, ',')) {
            produse.push_back(produs);
        }

        comenzi.emplace_back(nume_client, produse, pret_total);
    }

    return comenzi;
}

// CLIENTI
vector<Client> CSVHandler::citesteClienti(const string& filePathClienti) {
    vector<Client> clienti;
    ifstream fisier(filePathClienti);

    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului cu clienti: " << filePathClienti << endl;
        return clienti;
    }

    string linie;
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        stringstream ss(linie);
        string nume, totalCheltuitStr, numarComenziStr, reducereStr;

        getline(ss, nume, ',');
        getline(ss, totalCheltuitStr, ',');
        getline(ss, numarComenziStr, ',');
        getline(ss, reducereStr, ',');

        // conversie
        double totalCheltuit = stod(totalCheltuitStr);
        int numarComenzi = stoi(numarComenziStr);
        double reducere = stod(reducereStr);

        clienti.emplace_back(nume, totalCheltuit, numarComenzi, reducere);
    }

    fisier.close();
    return clienti;
}
void CSVHandler::scrieClienti(const string& filePathClienti, const vector<Client>& clienti) {
    ofstream fisier(filePathClienti, ios::trunc); // Suprascrie complet fișierul

    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului pentru scriere: " << filePathClienti << endl;
        return;
    }

    // Scriem antetul
    fisier << "nume,total cheltuit,numar comenzi,reducere\n";
    for (const auto& client : clienti) {
        fisier << client.getNume() << ","
               << client.getTotalCheltuit() << ","
               << client.getNumarComenzi() << ","
               << client.getReducere() << "\n";
    }

    if (fisier.fail()) {
        cerr << "Eroare la scrierea datelor în fișierul: " << filePathClienti << endl;
    }

    fisier.close();
}

// EVENIMENTE SPECIALE
vector<EvenimenteSpeciale> CSVHandler::citesteEvenimente(const string& filePathEvenimente) {
    vector<EvenimenteSpeciale> evenimente;
    ifstream fisier(filePathEvenimente);

    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului cu evenimente: " << filePathEvenimente << endl;
        return evenimente;
    }

    string linie;
    getline(fisier, linie); // antet

    while (getline(fisier, linie)) {
        stringstream ss(linie);
        string data, nume_eveniment;
        double cost;

        getline(ss, data, ',');
        getline(ss, nume_eveniment, ',');
        ss >> cost;

        evenimente.emplace_back(data, nume_eveniment, cost);
    }

    fisier.close();
    return evenimente;
}
void CSVHandler::scrieEvenimente(const string& filePathEvenimente, const vector<EvenimenteSpeciale>& evenimente) {
    ofstream fisier(filePathEvenimente);

    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului pentru scriere: " << filePathEvenimente << endl;
        return;
    }

    fisier << "data,nume_eveniment,cost\n";
    for (const auto& eveniment : evenimente) {
        fisier << eveniment.getData() << "," << eveniment.getNumeEveniment() << "," << eveniment.getCost() << "\n";
    }

    fisier.close();
}
void CSVHandler::adaugaEveniment(const string& filePathEvenimente, const EvenimenteSpeciale& eveniment) {
    ofstream fisier(filePathEvenimente, ios::app); // Deschide în modul de adăugare

    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului pentru adaugare: " << filePathEvenimente << endl;
        return;
    }

    fisier << eveniment.getData() << "," << eveniment.getNumeEveniment() << "," << eveniment.getCost() << "\n";
    fisier.close();
}

