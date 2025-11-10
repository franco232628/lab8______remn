//
// Created by GRINGO on 8/11/2025.
//

#ifndef LAB_8_AUXILIARYFUNCTIONS_HPP
#define LAB_8_AUXILIARYFUNCTIONS_HPP

#include "Utils.hpp"
void leer_infracciones(struct TablaDeInfracciones *arrTablaDeInfracciones,
                       int &cant_infracciones,
                       const char *file_name);
void open_read(ifstream &input, const char *file_name);
char *read_str(ifstream &input, char delim);
void to_upper(char &c);
void leer_empresas(struct EmpresasRegistradas *arrEmpresasRegistradas,
                   int &cant_empresas,
                   const char *file_name);
void leer_placas(struct EmpresasRegistradas *arrEmpresasRegistradas,
                 int cant_empresas,
                 const char *file_name);
void registrar_placa(int dni_leido,
                     char *placa_leida,
                     struct EmpresasRegistradas *arrEmpresasRegistradas,
                     int cant_empresas);
void leer_infraccionesCometidas(struct EmpresasRegistradas * arrEmpresasRegistradas,
    struct TablaDeInfracciones * arrTablaDeInfracciones,
    int cant_empresas,
    int cant_infracciones,
    const char *file_name);
int read_date( ifstream & input);
double buscarMulta(char * codigo_leido, struct TablaDeInfracciones * arrTablaDeInfracciones,
    int cant_infracciones);
void actualizarEmpresa(struct EmpresasRegistradas * arrEmpresasRegistradas,
    int cant_empresas,
    char * placa_leida,
    char p_or_n,
    int fecha_cometido,
    int fecha_pagado,
    double valor_multa);
void imprimir_reporte(struct EmpresasRegistradas *arr_empresas, int cant_empresas,
                      struct TablaDeInfracciones *arr_infrac, int cant_infrac,
                      const char *file_name);
void imprimir_reporte(struct EmpresasRegistradas *arrEmpresas,
                      int cantEmpresas,
                      struct TablaDeInfracciones *arrInfracciones,
                      int cantInfracciones,
                      const char *file_name) ;
void print_espacio( ofstream & output, int size, int num_placas);

#endif //LAB_8_AUXILIARYFUNCTIONS_HPP
