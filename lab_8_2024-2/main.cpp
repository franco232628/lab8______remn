#include "Biblioteca/AuxiliaryFunctions.hpp"




int main() {
    struct Distrito distrito[50];
    int cant_distrito = 0;
    leer_distrito(distrito,
                  cant_distrito,
                  "ArchivoDeDatos/lab8_Distritos.csv");
    // for (int i = 0; i < cant_distrito; i++) {
    //     cout << distrito[i].codigo << "   -    "
    //     << distrito[i].nombre << "    -    "
    //     << distrito[i].ubicacion << endl;
    // }
    struct Plato plato[120];
    int cant_plato = 0;
    leer_platosOfrecidos(plato, cant_plato, "ArchivoDeDatos/lab8_PlatosOfrecidos.csv");

    // for (int i = 0; i < cant_plato; i++) {
    //     cout << plato[i].codigo << "   -    "
    //     << plato[i].descripcion << "    -    "
    //     << plato[i].precio << "      -      "
    //     << plato[i].categoria << endl;
    // }
    struct Cliente cliente[110];
    int cant_cliente = 0;
    leer_cliente(cliente, cant_cliente, "ArchivoDeDatos/lab8_Clientes.csv");


    abrir_clientes(distrito, cant_distrito, plato, cant_plato, cliente,
                   cant_cliente, "ArchivoDeDatos/lab8_PedidosRealizados.txt");
    imprimirDistritos(distrito, cant_distrito);
    imprimirPlatos(plato, cant_plato);
    imprimirClientes(cliente, cant_cliente);
    return 0;
}
