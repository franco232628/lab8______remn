#include <iostream>
using namespace std;
#include "Bibliotecas/Facultad.h"

#include "Bibliotecas/Alumno.h"
#include "Bibliotecas/funciones.h"

int main() {
    struct Alumno arrAlumnos[100] {};
    int cantAlumnos=0;

    cargarCalificaciones(arrAlumnos, cantAlumnos);
    cargarAlumnos(arrAlumnos, cantAlumnos);
    actualizarFacultades(arrAlumnos, cantAlumnos);

    elaborarReporte(arrAlumnos, cantAlumnos);

    return 0;
}