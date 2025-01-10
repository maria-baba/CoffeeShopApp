#include "Produs.h"
#include "CSVHandler.h"
#include "EvenimenteSpeciale.h"
#include "Angajat.h"
#include "Barista.h"
#include "Ospatar.h"
#include "Manager.h"
#include "Comanda.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <regex>
#include <sstream>

using namespace std;

// Excepții personalizate
class InvalidCityException : public invalid_argument {
public:
    InvalidCityException() : invalid_argument("Oras invalid. Alege un oras din lista disponibila.") {}
};
class InvalidOptionException : public invalid_argument {
public:
    InvalidOptionException() : invalid_argument("Optiune invalida. Incearca din nou.") {}
};

bool valideazaData(const string& data);
string calculeazaZiSaptamana(const string& data);
void meniuBarista(const string& filePath);
void meniuOspatar(const string& filePathProduse, const string& filePathComenzi, const string& filePathClienti);
void meniuManager(const string& filePathAngajati, const string& filePathEvenimente, const string& filePathRaport, const string& filePathProduse, const string& filePathComenzi, const string& dataCurenta, const string& zi);

int main() {
    string dataCurenta;
    // data
    while (true) {
        cout << "Introduceti data curenta (format dd/mm/yyyy):\n";
        cin >> dataCurenta;

        if (valideazaData(dataCurenta)) {
            cout << "Calculele se vor desfasura in functie de data de astazi: " << dataCurenta << "\n\n";
            break;
        } else {
            cout << "Data introdusa este invalida. Va rugam sa incercati din nou.\n";
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string ziSaptamana = calculeazaZiSaptamana(dataCurenta);
    cout << "Ziua saptamanii pentru data de azi(!pentru raportul zilnic) (" << dataCurenta << ") este: " << ziSaptamana << "\n\n";

    vector<string> orase = {"Bucuresti", "Cluj-Napoca", "Iasi", "Brasov", "Timisoara"};

    // meniu orase
    while (true) {
        cout << "Alege orasul in care operezi (introdu numarul corespunzator):\n";
        for (size_t i = 0; i < orase.size(); ++i) {
            cout << i + 1 << ". " << orase[i] << endl;
        }
        cout << orase.size() + 1 << ". Iesire\n";

        int optiune;
        cout << "Alege o optiune:\n";
        cin >> optiune;

        try {
            if (optiune >= 1 && optiune <= orase.size()) {
                string oras = orase[optiune - 1];
                string angajatiPath = "Date/" + oras + "/angajati.csv";
                string produsePath = "Date/" + oras + "/produse.csv";
                string comenziPath = "Date/" + oras + "/comenzi.csv";
                string raport_financiarPath = "Date/" + oras + "/raport_financiar.csv";
                string clientiPath = "Date/" + oras + "/clienti.csv";
                string evenimente_specialePath = "Date/" + oras + "/evenimente_speciale.csv";

                vector<Angajat*> angajati = CSVHandler::citesteAngajati(angajatiPath);

                cout << "Introdu nume angajat:\n";
                cin.ignore();
                string numeAngajat;
                getline(cin, numeAngajat);

                auto it = find_if(angajati.begin(), angajati.end(),
                                  [&numeAngajat](Angajat* angajat) {
                                      return angajat->getNume() == numeAngajat;
                                  });

                if (it != angajati.end()) {
                    Angajat* angajat = *it;
                    cout << "Vei opera ca: " << angajat->getFunctie() << ".\n";

                    // meniuri pentru fiecare tip de angajat
                    if (angajat->getFunctie() == "manager") {
                        meniuManager(angajatiPath, evenimente_specialePath, raport_financiarPath, produsePath, comenziPath, dataCurenta, ziSaptamana);
                    } else if (angajat->getFunctie() == "barista") {
                        meniuBarista(produsePath);
                    } else if (angajat->getFunctie() == "ospatar") {
                        meniuOspatar(produsePath, comenziPath, clientiPath);
                    }
                } else {
                    cout << "Angajatul cu numele introdus nu a fost gasit. Revenire la selectarea orasului.\n";
                    continue;
                }

                // free memory
                for (Angajat* angajat : angajati) {
                    delete angajat;
                }
            } else if (optiune == orase.size() + 1) {
                cout << "Iesire din program.\n";
                break;
            } else {
                throw runtime_error("Optiune invalida.");
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}


bool valideazaData(const string& data) {
    // expresie regulată pentru formatul dd/mm/yyyy
    regex formatData(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(\d{4}))");

    // verificare format
    if (!regex_match(data, formatData)) {
        return false;
    }

    stringstream ss(data);
    string zi, luna, an;
    getline(ss, zi, '/');
    getline(ss, luna, '/');
    getline(ss, an);

    int ziInt = stoi(zi);
    int lunaInt = stoi(luna);
    int anInt = stoi(an);

    vector<int> zileLuni = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((anInt % 4 == 0 && anInt % 100 != 0) || (anInt % 400 == 0)) {
        zileLuni[1] = 29;
    }

    return lunaInt >= 1 && lunaInt <= 12 && ziInt >= 1 && ziInt <= zileLuni[lunaInt - 1];
}
string calculeazaZiSaptamana(const string& data) {
    // algoritm Zeller

    stringstream ss(data);
    string zi, luna, an;
    getline(ss, zi, '/');
    getline(ss, luna, '/');
    getline(ss, an);

    int ziInt = stoi(zi);
    int lunaInt = stoi(luna);
    int anInt = stoi(an);

    if (lunaInt == 1 || lunaInt == 2) {
        lunaInt += 12;
        anInt -= 1;
    }

    int K = anInt % 100;
    int J = anInt / 100;
    int ziSaptamana = (ziInt + (13 * (lunaInt + 1)) / 5 + K + (K / 4) + (J / 4) - 2 * J) % 7;

    // modifica rezultat negativ
    if (ziSaptamana < 0) {
        ziSaptamana += 7;
    }

    const string zile[] = {"sambata", "duminica", "luni", "marti", "miercuri", "joi", "vineri"};
    return zile[ziSaptamana];
}
void meniuBarista(const string& filePath) {
    vector<Produs> produse = CSVHandler::citesteProduse(filePath);

    while (true) {
        cout << "\n===== Meniu Barista =====\n";
        cout << "1. Adauga produs\n";
        cout << "2. Afiseaza produse\n";
        cout << "3. Sterge produs\n";
        cout << "4. Salveaza si iesi\n";
        cout << "Alege o optiune:\n";
        int suboptiune;
        cin >> suboptiune;

        try {
            if (suboptiune == 1) {
                while (true) {
                    Produs produsNou;
                    cout << "Incepti, va rog, introducerea datelor pentru produsul nou.\n";
                    cin >> produsNou;

                    // vf dacă produsul există deja
                    if (Produs::existaProdus(filePath, produsNou.getNume())) {
                        cout << "Produsul \"" << produsNou.getNume()
                             << "\" exista deja. Va rugam sa introduceti un alt produs.\n";
                    } else {
                        produse.push_back(produsNou);
                        CSVHandler::scrieProduse(filePath, produse);
                        cout << "Produs adaugat cu succes.\n";
                        break;
                    }
                }
            }
            else if (suboptiune == 2) {
                cout << "Produse in stoc:\n";
                //const nu modifica obiectul si auto determina tipul variabilei
                for (const auto& produs : produse) {
                    cout << produs << endl;
                }
            } else if (suboptiune == 3) {
                CSVHandler::stergeProdus(filePath, produse);
            } else if (suboptiune == 4) {
                CSVHandler::scrieProduse(filePath, produse);
                cout << "Datele au fost salvate.\n";
                break;
            } else {
                throw InvalidOptionException();
            }
        } catch (const InvalidOptionException& e) {
            cout << e.what() << endl;
        }

        cin.clear();
        // Ignorăm restul de pe linie
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void meniuOspatar(const string& filePathProduse, const string& filePathComenzi, const string& filePathClienti) {
    while (true) {
        cout << "\n===== Meniu Ospatar =====\n";
        cout << "1. Adauga comanda\n";
        cout << "2. Afiseaza comenzi\n";
        cout << "3. Salveaza si iesi\n";
        cout << "Alege o optiune:\n";
        int suboptiune;
        cin >> suboptiune;

        try {
            if (suboptiune == 1) {
                Comanda comanda;
                comanda.adaugaComanda(filePathProduse, filePathComenzi, filePathClienti);
            } else if (suboptiune == 2) {
                vector<Comanda> comenzi = CSVHandler::citesteComenzi(filePathComenzi);
                if (comenzi.empty()) {
                    cout << "Nu exista comenzi salvate.\n";
                } else {
                    cout << "Comenzi:\n";
                    for(const auto& comanda: comenzi) {
                        cout << comanda << endl;
                    }
                }
            } else if (suboptiune == 3) {
                cout << "Datele comenzilor au fost salvate.\n";
                break;
            } else {
                throw InvalidOptionException();
            }
        } catch (const InvalidOptionException& e) {
            cout << e.what() << endl;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void meniuManager(const string& filePathAngajati, const string& filePathEvenimente, const string& filePathRaport, const string& filePathProduse, const string& filePathComenzi, const string& dataCurenta, const string& zi) {
    int optiune;
    do {
        cout << "\n===== Meniu Manager =====\n";
        cout << "1. Adauga angajat\n";
        cout << "2. Sterge angajat\n";
        cout << "3. Modifica tura angajatului\n";
        cout << "4. Afiseaza toti angajatii\n";
        cout << "5. Adauga eveniment special\n";
        cout << "6. Sterge eveniment special\n";
        cout << "7. Afiseaza evenimente speciale\n";
        cout << "8. Genereaza raport financiar\n";
        cout << "9. Iesire\n";
        cout << "Alegeti o optiune:\n";
        cin >> optiune;

        switch (optiune) {
        case 1: {
            Angajat angajatNou;
            cin.ignore();
            cout << "Introduceti detaliile noului angajat:\n";
            cin >> angajatNou; // Citire folosind operatorul >> supraincarcat

            Manager::adaugaAngajat(filePathAngajati, angajatNou.getNume(), angajatNou.getFunctie(), angajatNou.getSalariuPeOra(), angajatNou.getTura());
            break;
        }
        case 2: {
            string nume;
            cin.ignore();
            cout << "\nIntroduceti numele angajatului de sters:\n";
            getline(cin, nume);
            Manager::stergeAngajat(filePathAngajati, nume);
            break;
        }
        case 3: {
            string nume;
            vector<string> turaNoua;
            cin.ignore();
            cout << "\nIntroduceti numele angajatului:\n";
            getline(cin, nume);

            cout << "Introduceti noile ture (introduceti 'stop' pentru a termina):\n";
            while (true) {
                string ziSiInterval;
                cout << "Tura (zi interval):\n";
                getline(cin, ziSiInterval);
                if (ziSiInterval == "stop") break;

                // Separa ziua de interval
                stringstream ss(ziSiInterval);
                string zi, interval;
                ss >> zi >> interval;

                // Verificăm dacă am obținut ambele valori
                if (ss.fail()) {
                    cout << "Format invalid. Va rugam introduceti din nou.\n";
                    continue; // Continuăm să cerem date corecte
                }

                // Adaugă ziua și intervalul în formatul dorit
                turaNoua.push_back(zi);
                turaNoua.push_back(interval);
            }

            Manager::schimbaTura(filePathAngajati, nume, turaNoua);
            break;
        }
        case 4: {
            cin.ignore();
            vector<Angajat*> angajati = CSVHandler::citesteAngajati(filePathAngajati);
            if (angajati.empty()) {
                cout << "Nu exista angajati salvati.\n";
            } else {
                cout << "Angajati:\n";
                for (const auto& angajat : angajati) {
                    cout << *angajat << endl;
                }
            }
            break;
        }
        case 5: {
            EvenimenteSpeciale eveniment;
            cin.ignore();
            cout << "\nIntroduceti detaliile evenimentului special:\n";

            string data, numeEveniment;
            double cost;

            while (true) {
                cout << "Data (format: dd/mm/yyyy):\n";
                getline(cin, data);

                if (valideazaData(data)) {
                    break;
                } else {
                    cout << "Data introdusa este invalida. Te rog, incearca din nou." << endl;
                }
            }
            cout << "Nume eveniment:\n";
            getline(cin, numeEveniment);
            cout << "Cost:\n";
            cin >> cost;
            cin.ignore(); // Elimină newline-ul

            eveniment = EvenimenteSpeciale(data, numeEveniment, cost);
            Manager::adaugaEvenimentSpecial(filePathEvenimente, eveniment);
            break;
        }
        case 6: {
            cin.ignore();
            string numeEveniment;
            cout << "\nIntroduceti numele evenimentului de sters:\n";
            getline(cin, numeEveniment);
            Manager::stergeEvenimentSpecial(filePathEvenimente, numeEveniment);
            break;
        }
        case 7: {
            cin.ignore();
            vector<EvenimenteSpeciale> evenimente = CSVHandler::citesteEvenimente(filePathEvenimente);
            if (evenimente.empty()) {
                cout << "Nu exista evenimente speciale salvate.\n";
            } else {
                cout << "Evenimente speciale:\n";
                for (const auto& eveniment : evenimente) {
                    cout << eveniment << endl;
                }
            }
            break;
        }
        case 8: {
            cin.ignore();
            Manager::genereazaRaportFinal(filePathComenzi, filePathProduse, filePathAngajati, filePathEvenimente, filePathRaport, dataCurenta, zi);
            cout << "Raportul financiar a fost generat.\n";
            break;
        }
        case 9:
            //cin.ignore();
            cout << "Iesire din meniul manager.\n";
            break;
        default:
            cin.ignore();
            cout << "Optiune invalida. Reincercati.\n";
            break;
        }
    } while (optiune != 9);
}
