cmake_minimum_required(VERSION 3.29)
project(PROIECT_POO)

set(CMAKE_CXX_STANDARD 20)

add_executable(PROIECT_POO main.cpp
        Produs.cpp
        Produs.h
        CSVHandler.cpp
        CSVHandler.h
        Angajat.cpp
        Angajat.h
        Comanda.cpp
        Comanda.h
        Manager.cpp
        Manager.h
        Ospatar.cpp
        Ospatar.h
        Barista.cpp
        Barista.h
        Client.cpp
        Client.h
        EvenimenteSpeciale.cpp
        EvenimenteSpeciale.h
)
