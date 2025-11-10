//
// Created by GRINGO on 8/11/2025.
//

#ifndef LAB_8_EMPRESASREGISTRADAS_HPP
#define LAB_8_EMPRESASREGISTRADAS_HPP
#include "Fecha.hpp"
struct EmpresasRegistradas {
    int dni;
    // char* nombre;
    // char* distrito;
    char nombre[100];
    char distrito[50];

    char* placas[10];
    int numPlacas;
    struct Fecha fechaDeInfraccion;
    struct Fecha fechaDePago;
    double totalMultas;
    double totalPagado;
    double totalAdeudado;
    int cantidadDeFaltas;
};

#endif //LAB_8_EMPRESASREGISTRADAS_HPP