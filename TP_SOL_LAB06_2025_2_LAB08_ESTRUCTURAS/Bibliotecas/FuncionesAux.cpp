//
// Created by AlienCoders on 7/11/2025.
//
#include "FuncionesAux.h"

void LeerStreams(struct Stream *arrStreams, int &cantStreams) {
    ifstream archStreams("ArchivosLectura/Reproducciones.txt", ios::in);
    if (not archStreams.is_open()) {
        cout<<"ERROR, no se pudo abrir Reproducciones.txt";
        exit(1);
    }

    int i=0;
    int dia, mes, anio;
    int hora, min, seg;
    char c;
    while (true) {
        archStreams>>dia>>c>>mes>>c>>anio;
        if (archStreams.eof()) break;
        arrStreams[i].fecha = anio*10000+mes*100+dia;

        archStreams>>arrStreams[i].canal>>arrStreams[i].codigo;
        archStreams>>arrStreams[i].rating>>arrStreams[i].dropoff;

        archStreams>>hora>>c>>min>>c>>seg;
        arrStreams[i].duracionSeg = hora*3600+min*60+seg;

        i++;
    }
    cantStreams = i;
}

void LeerCategoria(struct Categoria *arrCategorias, int &cantCategorias) {
    ifstream archCate("ArchivosLectura/Categorias.txt", ios::in);
    if (not archCate.is_open()) {
        cout<<"ERROR, no se pudo abrir Categorias.txt";
        exit(1);
    }

    int i=0;
    while (true) {
        archCate>>arrCategorias[i].codigo>>arrCategorias[i].nombre;
        if (archCate.eof()) break;
        i++;
    }
    cantCategorias = i;
}

void crearReportes(struct Stream *arrStreams, int cantStreams,
                   struct Categoria *arrCategorias, int cantCategorias) {

    char nombre[100], enlace[100];
    for (int i=0 ; i<cantCategorias ; i++) {
        formatearNombre(nombre, enlace, arrCategorias[i].nombre);
        ofstream archRepCat(nombre, ios::out);

        archRepCat<<"Codigo: "<<arrCategorias[i].codigo<<endl;
        archRepCat<<"Nombre: "<<arrCategorias[i].nombre<<endl;
        archRepCat<<"Enlace: "<<enlace<<endl;
        archRepCat<<"========================================"<<endl;
        for (int k=0 ; k<cantStreams ; k++) {
            if ( strcmp(arrCategorias[i].codigo, arrStreams[k].codigo)==0 ) {
                imprimirFecha(archRepCat, arrStreams[k].fecha);
                archRepCat<<setw(12)<<left<<arrStreams[k].canal;
                archRepCat<<fixed;
                archRepCat.precision(2);
                archRepCat<<setw(8)<<right<<arrStreams[k].rating;
                archRepCat<<setw(8)<<right<<arrStreams[k].dropoff;
                imprimirDuracion(archRepCat, arrStreams[k].duracionSeg);
                archRepCat<<endl;
            }
        }
    }


}

void formatearNombre(char *nombreArch, char* enlace, char* nombre) {
    strcpy(enlace, "https://Laboratorio07-2025-2/");
    strcpy(nombreArch, "ArchivosReporte/");
    char nombreArchEnlace[100];
    int p=0;

    bool mayus = true;
    int k=strlen(nombreArch);
    for (int i=0 ; nombre[i]!='\0' ; i++) {
        if (nombre[i]!='_' or nombre[i]!='-') {
            if ('0'<=nombre[i] and nombre[i]<='9') {
                nombreArch[k] = nombre[i];
                nombreArchEnlace[p] = nombre[i];
            }else{
                if (mayus) {
                    nombreArch[k] = nombre[i] - ('a'-'A');
                    nombreArchEnlace[p] = nombre[i] - ('a'-'A');
                    mayus = false;
                }else {
                    nombreArch[k] = nombre[i];
                    nombreArchEnlace[p] = nombre[i];
                }
            }
            k++;
            p++;
        }else {
            mayus = true;
        }
    }
    nombreArch[k] = 0;//fin de cadena
    nombreArchEnlace[p] = 0;

    strcat(enlace,nombreArchEnlace);
    strcat(nombreArch,".txt");
}

void imprimirFecha(ofstream &archRepCat, int fecha) {
    int dia=fecha%100;
    int mes=(fecha/100)%100;
    int anio=fecha%10000;
    archRepCat.fill('0');
    archRepCat<<setw(2)<<right<<dia<<"/"<<setw(2)<<right<<mes<<"/"<<setw(4)<<right<<anio;
    archRepCat.fill(' ');
    archRepCat<<"  ";
}

void imprimirDuracion(ofstream &archRepCat, int tiempoSeg) {
    int hora=tiempoSeg/3600;
    int min=(tiempoSeg%3600)/60;
    int seg=((tiempoSeg%3600)%60);
    archRepCat<<"  ";
    archRepCat.fill('0');
    archRepCat<<setw(2)<<right<<hora<<":"<<setw(2)<<right<<min<<":"<<setw(2)<<right<<seg;
    archRepCat.fill(' ');
    archRepCat<<"  ";
}