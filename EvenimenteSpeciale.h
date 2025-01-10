//
// Created by surug on 1/10/2025.
//

#ifndef EVENIMENTESPECIALE_H
#define EVENIMENTESPECIALE_H

#include <string>
#include <iostream>

using namespace std;

class EvenimenteSpeciale {
private:
    string data;
    string nume_eveniment;
    double cost;

public:
    EvenimenteSpeciale();;
    // Constructor
    EvenimenteSpeciale(const string& data, const string& nume_eveniment, double cost);

    // Getters
    string getData() const;
    string getNumeEveniment() const;
    double getCost() const;

    friend ostream& operator<<(std::ostream& os, const EvenimenteSpeciale& eveniment);
};

#endif //EVENIMENTESPECIALE_H
