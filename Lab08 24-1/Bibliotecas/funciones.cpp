#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#include "Facultad.h"
#include "Alumno.h"
#include "funciones.h"
#define ANCHO 160

void cargarCalificaciones(struct Alumno *arrAlumnos, int &cantAlumnos) {
    ifstream archCalificaciones;
    abrirInput(archCalificaciones, "ArchivosDeDatos/Calificaciones_laboratorio8.txt");

    double creditos;
    char *codCurso;

    // ARQ555   5.5   20196536   20   20236102   10   20222575   7   20194050   15...
    while (true) {
        codCurso = leerCadenaExacta(archCalificaciones, ' ');
        if (codCurso == nullptr) break; // nullptr: el leerCadenaExacta llego al eof

        archCalificaciones >> creditos;
        procesarNotas(archCalificaciones, arrAlumnos, cantAlumnos, creditos); // todavia no se que tan penalizable es poner dos whiles anidados, pero asi se ve mas limpio
    }

    for (int i=0; i < cantAlumnos; i++) { // actualizar promedios
        if (arrAlumnos[i].numCursos != 0)
            arrAlumnos[i].promPonderado = arrAlumnos[i].sumaPonderada / arrAlumnos[i].numCursos;
    }
}

void procesarNotas(ifstream &archCalificaciones, struct Alumno *arrAlumnos, int &cantAlumnos, double creditos) {
    int codAlumno, nota, pos;

    while (true) {
        if (archCalificaciones.peek() == '\n') break;

        archCalificaciones >> codAlumno >> nota;
        pos = buscarAlumno(arrAlumnos, codAlumno, cantAlumnos);

        if (pos == -1) { // si no esta, se agrega
            pos = cantAlumnos;
            arrAlumnos[cantAlumnos].codigo = codAlumno;
            cantAlumnos++;
        }
        arrAlumnos[pos].sumaPonderada += creditos * nota;
        arrAlumnos[pos].numCreditos += creditos;
        arrAlumnos[pos].numCursos++; // aunque un curso se repitiera en el txt, no volveria a poner la misma nota y el mismo alumno. Entonces no hay que verificar eso  (ojala)
    }
}

void cargarAlumnos(struct Alumno *arrAlumnos, int cantAlumnos) {
    // como actualizamos los arreglos anteriores, solo se tomaran en cuenta a los alumnos matriculados en al menos un curso para el reporte
    ifstream archAlumnos;
    abrirInput(archAlumnos, "ArchivosDeDatos/Alumnos_laboratorio8.csv");

    int codigo, pos;
    char *nombre, *codFacultad;

    // 20198237,CASTRO SUAREZ ROLANDO,EEGGCC
    while (true) {
        archAlumnos >> codigo;
        if (archAlumnos.eof()) break;

        archAlumnos.get(); // para comerse la comaxdxDxXxdx
        nombre = leerCadenaExacta(archAlumnos, ',');
        codFacultad = leerCadenaExacta(archAlumnos, '\n');

        pos = buscarAlumno(arrAlumnos, codigo, cantAlumnos);
        if (pos != -1) {
            // si hubieramos creado las estructuras con char* (puntero), aqui habria que leerCadenaExacta para asignarles su memoria dinamica
            strcpy(arrAlumnos[pos].nombre, nombre);
            strcpy(arrAlumnos[pos].facultad.codigo, codFacultad);
        }
    }
}

void actualizarFacultades(struct Alumno *arrAlumnos, int cantAlumnos) {
    /*
     * en esta parte hay que recorrer el arreglo de alumnos para asignar uno por uno su nombre de facultad
     * se puede leer varias veces el archivo con seekg como haciamos antes, pero tambien podemos usar la forma optimizada que enseñaron mas tarde en arreglos
     * se guarda la informacion que vamos a consultar varias veces y se busca el codigo de facultad para actualizar el nombre
     */

    int cantFacultades=0, posFacultad;
    char *arrNombre[10], *arrCodFacultad[10];

    cargarFacultades(arrNombre, arrCodFacultad, cantFacultades);

    for (int i=0; i < cantAlumnos; i++) {
        posFacultad = buscarFacultad(arrAlumnos[i].facultad.codigo, arrCodFacultad, cantFacultades); // pasamos un char*, un char** y un int
        if (posFacultad != -1) {
            strcpy(arrAlumnos[i].facultad.nombre, arrNombre[posFacultad]); // copiar(destino, origen)
        }
    }
}

void elaborarReporte(struct Alumno *arrAlumnos, int cantAlumnos) { // sin estructuras aqui ya habrian como 7 arreglos diferentes
    ofstream archReporte;
    abrirOutput(archReporte, "ArchivosDeReporte/ReporteDePagoPorAlumno.txt");
    archReporte << setprecision(2) << fixed;

    int posMayor;
    double numCreditosMayor=0;

    imprimirEncabezado(archReporte);

    for (int i=0; i < cantAlumnos; i++) {
        archReporte << left << arrAlumnos[i].codigo << " - " << setw(43) << arrAlumnos[i].nombre;
        archReporte << right << setw(4) << arrAlumnos[i].numCursos << setw(18) << arrAlumnos[i].sumaPonderada << setw(16) << arrAlumnos[i].numCreditos << setw(16) << arrAlumnos[i].promPonderado;
        archReporte << setw(9) << "" << arrAlumnos[i].facultad.nombre << endl;

        if (arrAlumnos[i].numCreditos > numCreditosMayor || numCreditosMayor == 0) {
            numCreditosMayor = arrAlumnos[i].numCreditos;
            posMayor = i;
        }
    }
    imprimirResumen(archReporte, arrAlumnos[posMayor]); // con la direccion donde esta la estructura ya tenemos toda la informacion necesaria
}

/* Funciones secundarias */

int buscarAlumno(struct Alumno *arrAlumnos, int codAlumno, int cantAlumnos) {
    for (int i = 0; i < cantAlumnos; i++) {
        if (arrAlumnos[i].codigo == codAlumno) return i;
    }
    return -1;
}

void cargarFacultades(char **arrNombre, char **arrCodFacultad, int &cantFacultades) {
    ifstream archFacultades;
    abrirInput(archFacultades, "ArchivosDeDatos/Facultades_laboratorio8.txt");

    // FACULTAD_DE_CIENCIAS_E_INGENIERIA   FDCI
    while (true) {
        arrNombre[cantFacultades] = leerCadenaExacta(archFacultades, ' ');
        if (arrNombre[cantFacultades] == nullptr) break;

        cambiarGuiones(arrNombre[cantFacultades]);
        arrCodFacultad[cantFacultades] = leerCadenaExacta(archFacultades, '\n');
        cantFacultades++;
    }
}

int buscarFacultad(char *AlumnoFacultadCod, char **arrCodFacultad, int cantFacultades) {
    for (int i=0; i < cantFacultades; i++) {
        if (strcmp(arrCodFacultad[i], AlumnoFacultadCod) == 0) return i;
    }
    return -1;
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(90) << "INSTITUCION EDUCATIVA_TP" << endl;
    archReporte << setw(103) << "PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS" << endl;
    archReporte << setw(85) << "CICLO: 2024-1" << endl;
    archReporte << setw(88) << "TODAS LAS FACULTADES" << endl;
    archReporte << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
    archReporte << setw(11) << "ALUMNO" << setw(53) << "No. de Cursos" << "  Suma Ponderada" << "  No. de Creditos" << "  Prom Ponderado" << "   Facultad" << endl;
    archReporte << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');
}

void imprimirResumen(ofstream &archReporte, const struct Alumno &AlumnoMayor) { // esto esta en el pdf de estructuras, pasar la direccion de la estructura (&) siempre y usar el const cuando no se le va a cambiar nada
    // en retrospectiva, es mas optimo pasar la direccion de la estructura que sus componentes por separado
    archReporte << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');
    archReporte << "Alumno con mayor numero de creditos matriculados:" << endl << setw(55);
    archReporte << AlumnoMayor.nombre << " [" << AlumnoMayor.codigo << "] con " << AlumnoMayor.numCreditos << " creditos de la " << AlumnoMayor.facultad.nombre << endl;
}

/* Funciones terciarias */

void abrirInput(ifstream &arch, const char* path) {
    arch.open(path, ios::in);
    if (!arch.is_open()) {
        cerr << "Error opening " << path << endl;
        exit(1);
    }
}

void abrirOutput(ofstream &arch, const char* path) {
    arch.open(path, ios::out);
    if (!arch.is_open()) {
        cerr << "Error opening " << path << endl;
        exit(1);
    }
}

char* leerCadenaExacta(ifstream &arch, char delimitador) { // el leerCadenaExacta de siempre pero adaptado para todo tipo de situaciones
    // si estan en txt y dejan usar arreglos estaticos pueden obviar esta funcion y usar el arch >> cadenaDeCaracteres
    char aux[100], *cad;

    arch >> ws;
    arch.getline(aux, 100, delimitador);
    if (arch.eof()) return nullptr;
    arch.clear();

    cad = new char[strlen(aux) + 1];
    strcpy(cad, aux);
    return cad;
}

void cambiarGuiones(char *cadena) {
    for (int i=0; cadena[i]; i++) {
        if (cadena[i] == '_') cadena[i] = ' ';
    }
}