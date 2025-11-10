#include "src/AuxiliaryFunctions.hpp"




int main() {
    struct TablaDeInfracciones arrTablaDeInfracciones[MAX_INFRA];
    int cantInfracciones = 0;

    leer_infracciones(arrTablaDeInfracciones,
                      cantInfracciones,
                      "data/TablaDeInfracciones_Lab08.csv");

    // for (int i = 0; i < cantInfracciones; i++) {
    //     cout << arrTablaDeInfracciones[i].codigo << "  -  "
    //         << arrTablaDeInfracciones[i].multa
    //         << arrTablaDeInfracciones[i].descripcion << endl;
    // }

    struct EmpresasRegistradas arrEmpresasRegistradas[MAX_EMPRESAS];
    int cantEmpresas = 0;
    leer_empresas(arrEmpresasRegistradas,
                  cantEmpresas,
                  "data/EmpresasRegistradas_Lab08.csv");



    leer_placas(arrEmpresasRegistradas,
                  cantEmpresas,
                  "data/PlacasRegistradas_Lab08.txt");
    // for (int i = 0; i < cantEmpresas; i++) {
    //     cout << arrEmpresasRegistradas[i].dni << "  -  "
    //         << arrEmpresasRegistradas[i].nombre << "  -  "
    //     << arrEmpresasRegistradas[i].distrito << "  -  ";
    //     for (int j =0; j< arrEmpresasRegistradas[i].numPlacas; j++) {
    //         cout << arrEmpresasRegistradas[i].placas[j]<<"  -  ";
    //     }
    //         cout << arrEmpresasRegistradas[i].numPlacas << endl;
    // }

    leer_infraccionesCometidas(arrEmpresasRegistradas, arrTablaDeInfracciones,
                        cantEmpresas, cantInfracciones,
                        "data/InfraccionesCometidas_Lab08.csv");
    // imprimir_reporte( arrEmpresasRegistradas, cantEmpresas,
    //                   arrTablaDeInfracciones, cantInfracciones,
    //                   "data/Reporte.csv");
    imprimir_reporte(arrEmpresasRegistradas, cantEmpresas,
                arrTablaDeInfracciones, cantInfracciones,
                "data/Reporte.txt");

    return 0;
}
