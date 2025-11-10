//
// Created by AlienCoders on 8/11/2025.
//

#ifndef TP_SOL_LAB08_2025_1_FUNCIONESAUX_H
#define TP_SOL_LAB08_2025_1_FUNCIONESAUX_H

#include<iostream>
#include<fstream>
using namespace std;
#include<cstring>

#include<iomanip>

#include "TablaDeInfracciones.h"
#include "Fecha.h"
#include "EmpresasRegistradas.h"

void LeerTablaInfracciones(struct TablaDeInfracciones *arrInfracciones, int &cantInfracciones);
void LeerEmpresas(struct EmpresaResgitrada *arrEmpresas, int &cantEmpresas);

void LeerPlacas(struct EmpresaResgitrada *arrEmpresas, int cantEmpresas);
void registrarPlaca(int dni, char *placa, struct EmpresaResgitrada *arrEmpresas, int cantEmpresas) ;

void LeerInfracciones(struct EmpresaResgitrada *arrEmpresas, int cantEmpresas,
                      struct TablaDeInfracciones *arrInfracciones, int cantInfracciones);
double BuscarValorMulta(char *codInfra, struct TablaDeInfracciones *arrInfracciones, int cantInfracciones);
void actualizarEmpresas(struct EmpresaResgitrada *arrEmpresas, int cantEmpresas, char *placa, char pago,
                        int dia, int mes, int anio, int diaPago, int mesPago, int anioPago, double valorMulta);


#endif //TP_SOL_LAB08_2025_1_FUNCIONESAUX_H