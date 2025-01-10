//
// Created by surug on 1/10/2025.
//

#include "EvenimenteSpeciale.h"

//
// Created by surug on 1/10/2025.
//

#include "EvenimenteSpeciale.h"
#include <iostream>

using namespace std;

EvenimenteSpeciale::EvenimenteSpeciale() {}
EvenimenteSpeciale::EvenimenteSpeciale(const string& data, const string& nume_eveniment, double cost)
    : data(data), nume_eveniment(nume_eveniment), cost(cost) {}

// Getter
string EvenimenteSpeciale::getData() const {
    return data;
}
string EvenimenteSpeciale::getNumeEveniment() const {
    return nume_eveniment;
}
double EvenimenteSpeciale::getCost() const {
    return cost;
}

// supraincarcare operator <<
ostream& operator<<(std::ostream& os, const EvenimenteSpeciale& eveniment) {
    os << "Data: " << eveniment.data << ", Nume: " << eveniment.nume_eveniment << ", Cost: " << eveniment.cost << " RON";
    return os;
}