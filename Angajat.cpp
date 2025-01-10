//
// Created by surug on 1/3/2025.
//

#include "Angajat.h"
#include <iomanip>
#include <stdexcept>

using namespace std;

Angajat::Angajat() : nume(""), functie(""), salariuPeOra(0.0), tura({}) {}
Angajat::Angajat(const string& nume, const string& functie, double salariuPeOra, const vector<string>& tura)
    : nume(nume), functie(functie), salariuPeOra(salariuPeOra), tura(tura) {}

string Angajat::getNume() const { return nume; }
string Angajat::getFunctie() const { return functie; }
double Angajat::getSalariuPeOra() const { return salariuPeOra; }
const vector<string>& Angajat::getTura() const { return tura; }
void Angajat::setTura(const vector<string>& turaNoua) { tura = turaNoua; }

void Angajat::afiseazaDetalii() const {
    cout << "Nume: " << nume << ", Functie: " << functie << ", Salariu pe ora: " << salariuPeOra << " lei\n";
}

// Supraincarcare operator <<
ostream& operator<<(ostream& os, const Angajat& angajat) {
    os << left << setw(20) << "Nume: " << angajat.nume << "\n" // Aliniere stânga
       << left << setw(20) << "Functie: " << angajat.functie << "\n"
       << left << setw(20) << "Salariu pe ora: " << angajat.salariuPeOra << "\n"
       << left << setw(20) << "Tura: ";

    for (size_t i = 0; i < angajat.tura.size(); ++i) {
        os << angajat.tura[i];
        if (i < angajat.tura.size() - 1) {
            os << ", ";
        }
    }

    os << endl;
    return os;
}

// Supraincarcare operator >>
istream& operator>>(istream& is, Angajat& angajat) {
    cout << "Introduceti numele:\n";
    getline(is, angajat.nume);

    cout << "Introduceti functia:\n";
    getline(is, angajat.functie);

    cout << "Introduceti salariul pe ora:\n";
    is >> angajat.salariuPeOra;
    is.ignore();

    angajat.tura.clear();
    cout << "Introduceti turele (format: zi interval; introduceti 'stop' pentru a termina):\n";

    string ziSiInterval;
    while (true) {
        cout << "Tura (zi interval):\n";
        getline(is, ziSiInterval);

        if (ziSiInterval == "stop") break;

        // separa ziua de interval
        stringstream ss(ziSiInterval);
        string zi, interval;

        // vf
        if (ss >> zi >> interval) {
            // Adaugă ziua și intervalul
            angajat.tura.push_back(zi);
            angajat.tura.push_back(interval);
        } else {
            cout << "Format invalid. Va rugam introduceti din nou.\n";
        }
    }

    return is;
}
