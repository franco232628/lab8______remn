//
// Created by Canales Zamora on 07/11/2025.
//

#ifndef TEST15_FUNCIONES_H
#define TEST15_FUNCIONES_H

void cargarCalificaciones(struct Alumno *arrAlumnos, int &cantAlumnos);
void procesarNotas(ifstream &archCalificaciones, struct Alumno *arrAlumnos, int &cantAlumnos, double creditos);
void cargarAlumnos(struct Alumno *arrAlumnos, int cantAlumnos);
void actualizarFacultades(struct Alumno *arrAlumnos, int cantAlumnos);
void elaborarReporte(struct Alumno *arrAlumnos, int cantAlumnos);

int buscarAlumno(struct Alumno *arrAlumnos, int codAlumno, int cantAlumnos);
void cargarFacultades(char **arrNombre, char **arrCodFacultad, int &cantFacultades);
int buscarFacultad(char *AlumnoFacultadCod, char **arrCodFacultad, int cantFacultades);
void imprimirEncabezado(ofstream &archReporte);
void imprimirResumen(ofstream &archReporte, const struct Alumno &AlumnoMayor);

void abrirInput(ifstream &arch, const char* path);
void abrirOutput(ofstream &arch, const char* path);
char* leerCadenaExacta(ifstream &arch, char delimitador);
void cambiarGuiones(char *cadena);

#endif //TEST15_FUNCIONES_H