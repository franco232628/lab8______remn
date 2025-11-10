#include <iostream>
using namespace std;

#include "Bibliotecas/Distrito.h"
#include "Bibliotecas/Plato.h"
#include "Bibliotecas/PlatoPedido.h"
#include "Bibliotecas/Cliente.h"
#include "Bibliotecas/funciones.h"

#define MAX_DISTRITOS 50 // lab8_Distritos.csv
#define MAX_PLATOS 120 // lab8_PlatosOfrecidos.csv
#define MAX_CLIENTES 110 // lab8_Clientes.csv

int main() { // con estructuras, toda esa nube de arreglos se simplifica asi
    struct Distrito arrDistritos[MAX_DISTRITOS] {};
    struct Plato arrPlatos[MAX_PLATOS] {};
    struct Cliente arrClientes[MAX_CLIENTES] {};

    int cantDistritos=0, cantPlatos=0, cantClientes=0;

    // cargado de archivos
    cargarDistritos(arrDistritos, cantDistritos);
    cargarPlatos(arrPlatos, cantPlatos);
    cargarClientes(arrClientes, cantClientes);

    // perder el tiempoSimple
    mostrarReporteSimpleDis(arrDistritos, cantDistritos);
    mostrarReporteSimplePla(arrPlatos, cantPlatos);
    mostrarReporteSimpleCli(arrClientes, cantClientes);

    // uso de lab8_PedidosRealizados.txt
    completarClientes(arrClientes, cantClientes, arrPlatos, cantPlatos, arrDistritos, cantDistritos);

    // el bubble sort de siempre pero con estructuras
    ordenarClientes(arrClientes, cantClientes);
    ordenarPedidos(arrClientes, cantClientes);

    // no se que hace estow
    elaborarReporte(arrClientes, cantClientes, arrPlatos, cantPlatos);

    return 0;
}