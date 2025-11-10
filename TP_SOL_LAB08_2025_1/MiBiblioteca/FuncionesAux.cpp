//
// Created by AlienCoders on 8/11/2025.
//

#include "FuncionesAux.h"

void LeerTablaInfracciones(struct TablaDeInfracciones *arrInfracciones, int &cantInfracciones) {
    ifstream archInfracciones("ArchivosLectura/TablaDeInfracciones.csv", ios::in);
    if (not archInfracciones.is_open()) {
        cout<<"Errot";
        exit(1);
    }
    int i=0;
    char c;
    while (true) {
            //L3001,214.55,Dejar mal estacionado el vehiculo en lugares permitidos.
        archInfracciones.getline(arrInfracciones[i].codigo, 10, ',');
        if (archInfracciones.eof())break;
        archInfracciones>>arrInfracciones[i].multa>>c;
        archInfracciones.getline(arrInfracciones[i].descripcion, 200, '\n');

        i++;
    }
    cantInfracciones = i;
}

void LeerEmpresas(struct EmpresaResgitrada *arrEmpresas, int &cantEmpresas) {
    ifstream archEmpresas("ArchivosLectura/EmpresasRegistradas.csv", ios::in);
    if (not archEmpresas.is_open()){
        cout<<"Errot";
        exit(1);
    }
    int i=0;
    char c;
    while (true) {
        archEmpresas>>arrEmpresas[i].dni>>c;
        if (archEmpresas.eof())break;
        archEmpresas.getline(arrEmpresas[i].nombre, 100, ',');
        archEmpresas.getline(arrEmpresas[i].distrito, 50, '\n');

        arrEmpresas[i].cantidadDeFaltas=0;
        arrEmpresas[i].numPlacas = 0;
        arrEmpresas[i].totalAdeudado = 0;
        arrEmpresas[i].totalMultas = 0;
        arrEmpresas[i].totalPagado = 0;

        arrEmpresas[i].fechaDeInfraccion = {0,0,0,99999999};//menor fecha
        arrEmpresas[i].fechaDePago = {0,0,0,0};;//mayor fecha

        i++;
    }
    cantEmpresas = i;
}


void LeerPlacas(struct EmpresaResgitrada *arrEmpresas, int cantEmpresas) {
    ifstream archPlacas("ArchivosLectura/PlacasRegistradas.txt", ios::in);
    if (not archPlacas.is_open()){
        cout<<"Errot";
        exit(1);
    }

    int dni;
    char placa[10];
    while (true) {
        archPlacas>>dni>>placa;
        if (archPlacas.eof())break;

        registrarPlaca(dni, placa, arrEmpresas, cantEmpresas);
    }
}

void registrarPlaca(int dni, char *placa, struct EmpresaResgitrada *arrEmpresas, int cantEmpresas) {
    for (int i=0 ; i<cantEmpresas ; i++) {
        if (dni == arrEmpresas[i].dni) {
            int indice = arrEmpresas[i].numPlacas;
            arrEmpresas[i].placas[indice] = new char[strlen(placa)+1];
            strcpy(arrEmpresas[i].placas[indice], placa);
            arrEmpresas[i].numPlacas++;
            break;
        }
    }
}


void LeerInfracciones(struct EmpresaResgitrada *arrEmpresas, int cantEmpresas,
                      struct TablaDeInfracciones *arrInfracciones, int cantInfracciones) {

    ifstream archInfracciones("ArchivosLectura/InfraccionesCometidas.csv", ios::in);
    if (not archInfracciones.is_open()){
        cout<<"Errot";
        exit(1);
    }

    int dia, mes, anio, diaPago, mesPago, anioPago;
    char placa[10], codInfra[10], c, pago;
    while (true) {
        archInfracciones>>dia>>c>>mes>>c>>anio>>c;
        if (archInfracciones.eof()) break;
        archInfracciones.getline(placa, 100, ',');
        archInfracciones.getline(codInfra, 100, ',');
        archInfracciones>>pago;
        if (pago=='P') {
            archInfracciones>>c>>diaPago>>c>>mesPago>>c>>anioPago;
        }

        double valorMulta = BuscarValorMulta(codInfra, arrInfracciones, cantInfracciones);
        actualizarEmpresas(arrEmpresas, cantEmpresas, placa, pago,
                           dia, mes, anio, diaPago, mesPago, anioPago, valorMulta);
    }

    cout<<"FIN";

}

double BuscarValorMulta(char *codInfra, struct TablaDeInfracciones *arrInfracciones, int cantInfracciones) {
    for (int i=0 ; i<cantInfracciones ; i++) {
        if ( strcmp(codInfra, arrInfracciones[i].codigo)==0 ) {
            return arrInfracciones[i].multa;
        }
    }
    return -1;
}

void actualizarEmpresas(struct EmpresaResgitrada *arrEmpresas, int cantEmpresas, char *placa, char pago,
                        int dia, int mes, int anio, int diaPago, int mesPago, int anioPago, double valorMulta) {

    for (int i=0 ; i<cantEmpresas ; i++) {//cada empresa
        for (int k=0 ; k<arrEmpresas[i].numPlacas ; k++) {//todas sus placas
            if ( strcmp(placa, arrEmpresas[i].placas[k]) == 0 ) {
                arrEmpresas[i].cantidadDeFaltas++;
                arrEmpresas[i].totalMultas+=valorMulta;
                if (pago=='P') arrEmpresas[i].totalPagado += valorMulta;
                else arrEmpresas[i].totalAdeudado += valorMulta;

                int fechaInfra = anio*10000+mes*100+dia;
                if (arrEmpresas[i].fechaDeInfraccion.fecha > fechaInfra)
                    arrEmpresas[i].fechaDeInfraccion = {dia, mes, anio, fechaInfra};

                int fechaPago = anioPago*10000+mesPago*100+diaPago;
                if (pago=='P')
                    if (arrEmpresas[i].fechaDePago.fecha > fechaPago)
                        arrEmpresas[i].fechaDePago = {diaPago, mesPago, anioPago, fechaPago};

                break;
            }
        }
    }

}