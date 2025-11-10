//
// Created by AlienCoders on 7/11/2025.
//

#ifndef TP_SOL_LAB06_2025_2_LAB08_ESTRUCTURAS_FUNCIONESAUX_H
#define TP_SOL_LAB06_2025_2_LAB08_ESTRUCTURAS_FUNCIONESAUX_H

#include<iostream>
#include<fstream>
using namespace std;
#include<cstring>
#include<iomanip>

#include"Categoria.h"
#include"Stream.h"

void LeerStreams(struct Stream *arrStreams, int &cantStreams);
void LeerCategoria(struct Categoria *arrCategorias, int &cantCategorias);

void crearReportes(struct Stream *arrStreams, int cantStreams,
                   struct Categoria *arrCategorias, int cantCategorias);
void formatearNombre(char *nombreArch, char* enlace, char* nombre) ;

void imprimirFecha(ofstream &archRepCat, int fecha);

void imprimirDuracion(ofstream &archRepCat, int tiempoSeg);

#endif //TP_SOL_LAB06_2025_2_LAB08_ESTRUCTURAS_FUNCIONESAUX_H