//
// Created by AlienCoders on 8/11/2025.
//

#ifndef TP_SOL_LAB08_2025_1_EMPRESASREGISTRADAS_H
#define TP_SOL_LAB08_2025_1_EMPRESASREGISTRADAS_H

#include "Fecha.h"

struct EmpresaResgitrada {
    int dni;
    char nombre[100];
    char distrito[50];
    char* placas[10];
    int numPlacas;
    struct Fecha fechaDeInfraccion;//
    struct Fecha fechaDePago;//
    double totalMultas;//
    double totalPagado;//
    double totalAdeudado;//
    int cantidadDeFaltas;//
};


#endif //TP_SOL_LAB08_2025_1_EMPRESASREGISTRADAS_H