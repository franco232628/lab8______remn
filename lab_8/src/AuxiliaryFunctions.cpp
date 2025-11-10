//
// Created by GRINGO on 8/11/2025.
//

#include "AuxiliaryFunctions.hpp"

void open_read(ifstream &input, const char *file_name) {
    input.open(file_name, ios::in);
    if (!input.is_open()) {
        cout << "Error opening file " << file_name << endl;
        exit(1);
    }
}


void leer_infracciones(struct TablaDeInfracciones *arr_infracciones,
                       int &cant_infracciones,
                       const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    // struct TablaDeInfracciones c;
    //L3001,214.55,Dejar mal estacionado el vehiculo en lugares permitidos.
    // char* codigo_leido;para lop dinamico;
    //para estatico:
    char c;
    while (true) {
        // codigo_leido = read_str(input, ','); // para lo dinamico
        input.getline(arr_infracciones[cant_infracciones].codigo, 10, ',');
        if (input.eof()) break;
        // c.codigo = codigo_leido; //para lo dinamico
        input >> arr_infracciones[cant_infracciones].multa >> c;
        input.getline(arr_infracciones[cant_infracciones].descripcion, 200, '\n');
        for (int i = 0; arr_infracciones[cant_infracciones].descripcion[i]; i++) {
            if (arr_infracciones[cant_infracciones].descripcion[i] >= 'a'
                and arr_infracciones[cant_infracciones].descripcion[i] <= 'z')
                to_upper(arr_infracciones[cant_infracciones].descripcion[i]);
        }
        cant_infracciones++;
    }
}

char *read_str(ifstream &input, char delim) {
    char *str, buffer[MAX_CARAC];
    input.getline(buffer, MAX_CARAC, delim);
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}

void to_upper(char &c) {
    c = c - ('a' - 'A');
}

void leer_empresas(struct EmpresasRegistradas *arrEmpresasRegistradas, int &cant_empresas, const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    //79672079,contreras chang johana cinthia,Chorrillos
    char c;
    while (true) {
        input >> arrEmpresasRegistradas[cant_empresas].dni >> c;
        if (input.eof()) break;
        input.getline(arrEmpresasRegistradas[cant_empresas].nombre, 100, ',');
        input.getline(arrEmpresasRegistradas[cant_empresas].distrito, 50, '\n');


        arrEmpresasRegistradas[cant_empresas].numPlacas = 0;
        arrEmpresasRegistradas[cant_empresas].totalMultas = 0;
        arrEmpresasRegistradas[cant_empresas].totalPagado = 0;
        arrEmpresasRegistradas[cant_empresas].totalAdeudado = 0;
        arrEmpresasRegistradas[cant_empresas].cantidadDeFaltas = 0;

        arrEmpresasRegistradas[cant_empresas].fechaDeInfraccion = {0, 0, 0, 99999999}; //mayor fecha
        arrEmpresasRegistradas[cant_empresas].fechaDePago = {0, 0, 0, 0}; //menor fecha


        for (int i = 0; arrEmpresasRegistradas[cant_empresas].nombre[i]; i++) {
            if (arrEmpresasRegistradas[cant_empresas].nombre[i] >= 'a'
                and arrEmpresasRegistradas[cant_empresas].nombre[i] <= 'z')
                to_upper(arrEmpresasRegistradas[cant_empresas].nombre[i]);
        }
        for (int i = 0; arrEmpresasRegistradas[cant_empresas].distrito[i]; i++) {
            if (arrEmpresasRegistradas[cant_empresas].distrito[i] >= 'a'
                and arrEmpresasRegistradas[cant_empresas].distrito[i] <= 'z')
                to_upper(arrEmpresasRegistradas[cant_empresas].distrito[i]);
        }
        cant_empresas++;
    }
}


void leer_placas(struct EmpresasRegistradas *arrEmpresasRegistradas,
                 int cant_empresas,
                 const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    int dni_leido;
    char placa_leida[10];
    while (true) {
        input >> dni_leido;
        if (input.eof()) break;
        input >> placa_leida;
        registrar_placa(dni_leido, placa_leida, arrEmpresasRegistradas, cant_empresas);
    }
}

void registrar_placa(int dni_leido,
                     char *placa_leida,
                     struct EmpresasRegistradas *arrEmpresasRegistradas,
                     int cant_empresas) {
    for (int i = 0; i < cant_empresas; i++) {
        //79672079,contreras chang johana cinthia,Chorrillos
        if (dni_leido == arrEmpresasRegistradas[i].dni) {
            int indice = arrEmpresasRegistradas[i].numPlacas; //0 al inicio // si se repite aqui hay 1
            arrEmpresasRegistradas[i].placas[indice] = new char[strlen(placa_leida) + 1];
            strcpy(arrEmpresasRegistradas[i].placas[indice], placa_leida);
            arrEmpresasRegistradas[i].numPlacas++; // pone 1
            break;
        }
    }
}


void leer_infraccionesCometidas(struct EmpresasRegistradas *arrEmpresasRegistradas,
                                struct TablaDeInfracciones *arrTablaDeInfracciones,
                                int cant_empresas,
                                int cant_infracciones,
                                const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    int fecha_cometido, fecha_pagado;
    char placa_leida[10], codigo_leido[10], p_or_n;
    //ejemplo del csv:
    // //1/12/2020,G760-721,G2022,N
    // 23/7/2023,P474-593,G2060,P,22/8/2023
    // 18/12/2024,G938-342,G2061,P,26/1/2025
    while (true) {
        fecha_cometido = read_date(input);
        if (input.eof()) break;
        input.get();
        input.getline(placa_leida, 10, ',');
        input.getline(codigo_leido, 10, ',');
        input >> p_or_n;
        if (p_or_n == 'P') {
            input.get();
            fecha_pagado = read_date(input);
        }
        double valor_multa = buscarMulta(codigo_leido, arrTablaDeInfracciones,
                                         cant_infracciones);
        actualizarEmpresa(arrEmpresasRegistradas, cant_empresas,
                          placa_leida, p_or_n, fecha_cometido,
                          fecha_pagado, valor_multa);
    }
}

void actualizarEmpresa(struct EmpresasRegistradas *arrEmpresasRegistradas,
                       int cant_empresas,
                       char *placa_leida,
                       char p_or_n,
                       int fecha_cometido,
                       int fecha_pagado,
                       double valor_multa) {
    for (int i = 0; i < cant_empresas; i++) {
        //para cada empresa
        for (int j = 0; j < arrEmpresasRegistradas[i].numPlacas; j++) {
            //placas
            if (strcmp(arrEmpresasRegistradas[i].placas[j], placa_leida) == 0) {
                arrEmpresasRegistradas[i].cantidadDeFaltas++;
                arrEmpresasRegistradas[i].totalMultas += valor_multa;
                if (p_or_n == 'P') arrEmpresasRegistradas[i].totalPagado += valor_multa;
                else arrEmpresasRegistradas[i].totalAdeudado += valor_multa;

                if (arrEmpresasRegistradas[i].fechaDeInfraccion.AAAAMMDD > fecha_cometido)
                    arrEmpresasRegistradas[i].fechaDeInfraccion = {
                        fecha_cometido % 100, (fecha_cometido / 100) % 100, fecha_cometido / 10000, fecha_cometido
                    };

                if (p_or_n == 'P')
                    if (arrEmpresasRegistradas[i].fechaDePago.AAAAMMDD < fecha_pagado)
                        arrEmpresasRegistradas[i].fechaDePago = {
                            fecha_pagado % 100, (fecha_pagado / 100) % 100, fecha_pagado / 10000, fecha_pagado
                        };

                break;
            }
        }
    }
}


int read_date(ifstream &input) {
    int dd, mm, aaaa;
    char c;
    input >> dd >> c >> mm >> c >> aaaa;
    return aaaa * 10000 + mm * 100 + dd;
}

double buscarMulta(char *codigo_leido, struct TablaDeInfracciones *arrTablaDeInfracciones,
                   int cant_infracciones) {
    for (int i = 0; i < cant_infracciones; i++) {
        if (strcmp(codigo_leido, arrTablaDeInfracciones[i].codigo) == 0) {
            return arrTablaDeInfracciones[i].multa;
        }
    }
    return -1;
}




void imprimir_reporte(struct EmpresasRegistradas *arrEmpresas,
                      int cantEmpresas,
                      struct TablaDeInfracciones *arrInfracciones,
                      int cantInfracciones,
                      const char *file_name) {
    ofstream output(file_name, ios::out);
    if (!output.is_open()) {
        cout << "Error al crear el archivo de reporte\n";
        exit(1);
    }

    output << "MINISTERIO DE TRANSPORTES\n";
    output << "LISTADO DE INFRACCIONES POR EMPRESA\n";
    output << string(100, '=') << "\n\n";
    output << "EMPRESA\n";
    output << string(100, '=') << "\n";
    output << "No.  DNI        NOMBRE               DISTRITO           PLACAS                   "
            "FECHA INF. MAS ANTIGUA  FECHA PAGO MAS RECIENTE  TOTAL PAGADO  TOTAL DEUDA  CANT. FALTAS\n";
    output << string(100, '-') << "\n";

    // EMPRESAS
    for (int i = 0; i < cantEmpresas; i++) {
        output << setw(2) << right << (i + 1) << ") "
                << setw(10) << arrEmpresas[i].dni << "  "
                << setw(45) << left << arrEmpresas[i].nombre << "  "
                << setw(30) << left << arrEmpresas[i].distrito << "  ";

        // Mostrar todas las placas separadas por '/'

        for (int j = 0; j < arrEmpresas[i].numPlacas; j++) {
            output << arrEmpresas[i].placas[j];
            if (j < arrEmpresas[i].numPlacas - 1)
                output << "/";

        }
        print_espacio(output, 50, arrEmpresas[i].numPlacas);

        // Fechas
        output << "   ";
        if (arrEmpresas[i].fechaDeInfraccion.AAAAMMDD == 99999999)
            output << "0";
        else
            output << setw(2) << setfill('0') << arrEmpresas[i].fechaDeInfraccion.dd << "/"
                    << setw(2) << arrEmpresas[i].fechaDeInfraccion.mm << "/"
                    << setw(4) << arrEmpresas[i].fechaDeInfraccion.aa;
        output << "   ";

        if (arrEmpresas[i].fechaDePago.AAAAMMDD == 0)
            output << "0";
        else
            output << setw(2) << setfill('0') << arrEmpresas[i].fechaDePago.dd << "/"
                    << setw(2) << arrEmpresas[i].fechaDePago.mm << "/"
                    << setw(4) << arrEmpresas[i].fechaDePago.aa;

        output << setfill(' ') << "   "
                << fixed << setprecision(2)
                << setw(10) << arrEmpresas[i].totalPagado << "   "
                << setw(10) << arrEmpresas[i].totalAdeudado << "   "
                << setw(3) << arrEmpresas[i].cantidadDeFaltas << "\n";
    }

    output << string(100, '=') << "\n\n";
    output << "TABLA DE INFRACCIONES\n";
    output << string(100, '=') << "\n";
    output << "CODIGO   MULTA    DESCRIPCION\n";
    output << string(100, '-') << "\n";

    // INFRACCIONES
    for (int i = 0; i < cantInfracciones; i++) {
        output << left << setw(8) << arrInfracciones[i].codigo << "  "
                << right << setw(8) << fixed << setprecision(2) << arrInfracciones[i].multa << "  "
                << left << arrInfracciones[i].descripcion << "\n";
    }

    output << string(100, '=') << "\n";
    output.close();
}

void print_espacio(ofstream &output, int size, int num_placas) {
    int espacio_faltante= size-(num_placas*9);
    for (int i=0; i < espacio_faltante; i++) output.put(' ');
}


