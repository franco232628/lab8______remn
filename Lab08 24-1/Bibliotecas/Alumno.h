//
// Created by Canales Zamora on 07/11/2025.
//

#ifndef TEST15_ALUMNO_H
#define TEST15_ALUMNO_H

struct Alumno {
    int codigo;
    char nombre[50];
    int numCursos;
    double sumaPonderada;
    double numCreditos;
    double promPonderado;
    struct Facultad facultad;
};

#endif //TEST15_ALUMNO_H