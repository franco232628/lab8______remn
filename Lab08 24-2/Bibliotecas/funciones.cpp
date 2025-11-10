#include <chrono>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#include "Distrito.h"
#include "Plato.h"
#include "PlatoPedido.h"
#include "Cliente.h"
#include "funciones.h"

#define ANCHO 130

void cargarDistritos(struct Distrito *arrDistritos, int &cantDistritos) {
    ifstream archDistritos;
    abrirInput(archDistritos, "ArchivosDeDatos/lab8_Distritos.csv");

    // LO9222,Surquillo,OESTE
    while (true) {
        arrDistritos[cantDistritos].codigo = leerCadenaExacta(archDistritos, ',');
        if (arrDistritos[cantDistritos].codigo == nullptr) break; // nullptr: leerCadenaExacta llego al eof

        arrDistritos[cantDistritos].nombre = leerCadenaExacta(archDistritos, ',');
        arrDistritos[cantDistritos].ubicacion = leerCadenaExacta(archDistritos, '\n');
        cantDistritos++;
    }
}

void cargarPlatos(struct Plato *arrPlatos, int &cantPlatos) {
    ifstream archPlatos;
    abrirInput(archPlatos, "ArchivosDeDatos/lab8_PlatosOfrecidos.csv");

    // AD-53814,PALTA,9.90,ADICIONAL
    while (true) {
        arrPlatos[cantPlatos].codigo = leerCadenaExacta(archPlatos, ',');
        if (arrPlatos[cantPlatos].codigo == nullptr) break;

        arrPlatos[cantPlatos].descripcion = leerCadenaExacta(archPlatos, ',');
        archPlatos >> arrPlatos[cantPlatos].precio;
        archPlatos.get(); // el getline quita la coma (delimitador) por defecto, pero el arch >> no lo hace
        arrPlatos[cantPlatos].categoria = leerCadenaExacta(archPlatos, '\n');
        cantPlatos++;
    }
}

void cargarClientes(struct Cliente *arrClientes, int &cantClientes) {
    ifstream archClientes;
    abrirInput(archClientes, "ArchivosDeDatos/lab8_Clientes.csv");

    // 92980780,VEGA MUNOZ GONZALO ,LO4439
    while (true) {
        archClientes >> arrClientes[cantClientes].dni;
        if (archClientes.eof()) break;

        archClientes.get();
        arrClientes[cantClientes].nombre = leerCadenaExacta(archClientes, ',');
        arrClientes[cantClientes].distrito.codigo = leerCadenaExacta(archClientes, '\n');

        cantClientes++;
    }
}

void mostrarReporteSimpleDis(struct Distrito *arrDistritos, int cantDistritos) {
    ofstream archSimpleDis;
    abrirOutput(archSimpleDis, "ArchivosDeReporte/reporteSimpleDistritos.txt");

    archSimpleDis << "DATOS DE DISTRITOS" << endl;
    archSimpleDis << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
    archSimpleDis << "CODIGO" << setw(20) << "NOMBRE" << setw(29) << "UBICACION" << endl;
    archSimpleDis << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');

    for (int i=0; i < cantDistritos; i++) {
        archSimpleDis << left << setw(20) << arrDistritos[i].codigo << setw(26) << arrDistritos[i].nombre << arrDistritos[i].ubicacion << endl;
    }
}

void mostrarReporteSimplePla(struct Plato *arrPlatos, int &cantPlatos) {
    ofstream archSimplePla;
    abrirOutput(archSimplePla, "ArchivosDeReporte/reporteSimplePlatos.txt");
    archSimplePla << setprecision(2) << fixed;

    archSimplePla << "DATOS DE PLATOS" << endl;
    archSimplePla << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');

    // cuando dicen que hagamos un reporte simple especifican los componentes, pero no como ordenar los subtitulos
    // aprovechen para poner esa cadena larga que es dificil de acomodar (DESCRIPCION) al final
    archSimplePla << "CODIGO" << setw(20) << "PRECIO" << setw(20) << "CATEGORIA" << setw(20) << "DESCRIPCION" << endl;
    archSimplePla << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');

    for (int i=0; i < cantPlatos; i++) {
        archSimplePla << arrPlatos[i].codigo << setw(18) << arrPlatos[i].precio << setw(11) << "";
        archSimplePla << left << setw(18) << arrPlatos[i].categoria << arrPlatos[i].descripcion << endl << right;
    }
}

void mostrarReporteSimpleCli(struct Cliente *arrClientes, int cantClientes) {
    ofstream archClientes;
    abrirOutput(archClientes, "ArchivosDeReporte/reporteSimpleClientes.txt");

    archClientes << "DATOS DE CLIENTES" << endl;
    archClientes << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
    archClientes << "DNI" << setw(20) << "DISTRITO" << setw(18) << "NOMBRE" << endl;
    archClientes << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');

    for (int i=0; i < cantClientes; i++) {
        archClientes << arrClientes[i].dni << setw(7) << "";
        archClientes << left << setw(20) << arrClientes[i].distrito.codigo << arrClientes[i].nombre << endl << right;
    }
}

void    completarClientes(struct Cliente *arrClientes, int cantClientes, struct Plato *arrPlatos, int cantPlatos, struct Distrito *arrDistritos, int cantDistritos) {
    ifstream archPedidos;
    abrirInput(archPedidos, "ArchivosDeDatos/lab8_PedidosRealizados.txt");

    int codPedido, dni, numPlatosPed,
         posCliente, posPlato, posDistrito;
    char codPlato[10]; // el 9 tambien sirve pero me gusta el 10

    // 615768    92980780        PO-11471       10
    while (true) {
        archPedidos >> codPedido;
        if (archPedidos.eof()) break;

        archPedidos >> dni >> codPlato >> numPlatosPed;

        posCliente = buscarCliente(arrClientes, dni, cantClientes);
        posPlato = buscarPlato(arrPlatos, codPlato, cantPlatos);
        if (posCliente != -1 && posPlato != -1) { // sin cliente o plato no hay nada que hacer
            insertarPedido(arrClientes[posCliente], arrPlatos[posPlato], codPedido, numPlatosPed); // al inicio pense que habia que acumular segun codigo de pedido. En realidad, solo es insertar desordenado
        }
    }

    for (int i=0; i < cantClientes; i++) {
        // actualizando distrito
        posDistrito = buscarDistrito(arrDistritos, arrClientes[i].distrito.codigo, cantDistritos);
        if (posDistrito != -1) {
            delete arrClientes[i].distrito.codigo; // este es un añadido personal para despejar el espacio asignado a la copia almacenada de codDistrito en Clientes.csv
            arrClientes[i].distrito = arrDistritos[posDistrito]; // crear estructuras es como crear nuevos tipos de variables, tambien pueden igualarse asi
        }

        // actualizando montoTotal
        arrClientes[i].montoTotal = sumarSubtotales(arrClientes[i]);
    }
}

int buscarDistrito(struct Distrito *arrDistritos, char *codDistrito, int cantDistritos) {
    for (int i=0; i < cantDistritos; i++) {
        if (strcmp(arrDistritos[i].codigo, codDistrito) == 0) return i;
    }
    return -1;
}


void ordenarClientes(struct Cliente *arrClientes, int cantClientes) {
    for (int i=0; i < cantClientes-1; i++) {
        for (int j=i+1; j < cantClientes; j++) {
            /*
             * truco al ordenar: piensen en la situacion de orden que seria un problema
             * aqui piden orden ascendente, seria un error que el anterior sea mayor al siguiente
             */
            if (strcmp(arrClientes[i].nombre, arrClientes[j].nombre) > 0) {
                cambiarClientes(arrClientes[i], arrClientes[j]); // ya no hay que hacer varios cambiarInt o cambiarDouble
            }
        }
    }
}

void ordenarPedidos(struct Cliente *arrClientes, int cantClientes) {
    for (int k=0; k < cantClientes; k++) { // para cada cliente, vamos a ordenar en su arreglo de pedidos

        // Arreglo: arrClientes[k].pedidos
        // Contador: arrClientes[k].cantidadDePedidos
        for (int i=0; i < arrClientes[k].cantidadDePedidos-1; i++) {
            for (int j=i+1; j < arrClientes[k].cantidadDePedidos-1; j++) { // misma estructura, diferentes palabras
                if (arrClientes[k].pedidos[i].codigoPedido > arrClientes[k].pedidos[j].codigoPedido ||
                     arrClientes[k].pedidos[i].codigoPedido == arrClientes[k].pedidos[j].codigoPedido && strcmp(arrClientes[k].pedidos[i].codigoPlato, arrClientes[k].pedidos[j].codigoPlato) < 0) {
                    cambiarPedidos(arrClientes[k].pedidos[i], arrClientes[k].pedidos[j]);
                }
            }
        }
    }
}

void elaborarReporte(struct Cliente *arrClientes, int cantClientes, struct Plato *arrPlatos, int cantPlatos) {
    ofstream archReporte;
    abrirOutput(archReporte, "ArchivosDeReporte/Pedidos_Atendidos.txt");
    archReporte << setprecision(2) << fixed;

    imprimirEncabezado(archReporte); // puede que por esta vez sea innecesario hacer esto en una funcion
    for (int i=0; i < cantClientes; i++) {
        archReporte << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
        archReporte << "CLIENTE No. " << setw(3) << setfill('0') << i+1 << endl << setfill(' ');
        archReporte << "DNI" << setw(13) << "NOMBRE" << setw(40) << "DISTRITO" << setw(29) << "PAGO TOTAL" << endl;
        archReporte << arrClientes[i].dni << "  " << left << setw(38) << arrClientes[i].nombre << setw(8) << arrClientes[i].distrito.codigo << setw(19) << arrClientes[i].distrito.nombre << arrClientes[i].montoTotal << endl << right;

        if (arrClientes[i].cantidadDePedidos > 0) imprimirPedidos(archReporte, arrClientes[i].pedidos, arrClientes[i].cantidadDePedidos, arrPlatos, cantPlatos); // no creo que se de el caso contrario pero ahi esta
    }
    cout << "jueguen touhou 8";
}

void imprimirPedidos(ofstream &archReporte, struct PlatoPedido *pedidos, int cantPedidos, struct Plato *arrPlatos, int cantPlatos) {
    int posPlato;

    archReporte << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');
    archReporte << setw(10) << "" << "PEDIDOS REALIZADOS:" << endl;
    archReporte << setw(13) << "NO." << "  PEDIDO" << "  CODIGO" << "     DESCRIPCION";
    archReporte << setw(46) << "CATEGORIA" << setw(12) << "PRECIO" << setw(12) << "CANTIDAD" << setw(11) << "SUBTOTAL" << endl;

    for (int i=0; i < cantPedidos; i++) {
        // no nos mandaron hacer un campo en PlatoPedido para guardar la categoria, por eso necesitamos buscar en arrPlatos
        posPlato = buscarPlato(arrPlatos, pedidos[i].codigoPlato, cantPlatos);

        archReporte << setw(10) << "" << setw(3) << setfill('0') << i+1 << "  " << setfill(' ');
        archReporte << pedidos[i].codigoPedido << setw(10) << pedidos[i].codigoPlato << "   ";
        archReporte << left << setw(48) << pedidos[i].descripcion << setw(13);
        if (posPlato != -1) archReporte << arrPlatos[posPlato].categoria;
        else archReporte << "NO ENCONTRADA"; // no creo que se de este caso pero ahi esta

        archReporte << right << setw(7) << pedidos[i].precio << setw(10) << pedidos[i].cantidad << setw(13) << pedidos[i].subtotal << endl;
    }
}

/* Funciones secundarias */

int buscarCliente(struct Cliente *arrClientes, int dni, int cantClientes) {
    for (int i=0; i < cantClientes; i++) {
        if (arrClientes[i].dni == dni) return i;
    }
    return -1;
}

int buscarPedido(const struct Cliente &ClienteElegido, int codPedido) { // recordar que es buena practica pasar las estructuras (no confundir con arreglos de estructuras) con '&', si no las van a modificar le ponen el "const"
    for (int i=0; i < ClienteElegido.cantidadDePedidos; i++) {
        if (ClienteElegido.pedidos[i].codigoPedido == codPedido) return i;
    }
    return -1;
}

int buscarPlato(struct Plato *arrPlatos, char *codPlato, int cantPlatos) {
    for (int i=0; i < cantPlatos; i++) {
        if (strcmp(arrPlatos[i].codigo, codPlato) == 0) return i;
    }
    return -1;
}

void insertarPedido(struct Cliente &ClienteElegido, const struct Plato &PlatoElegido, int codPedido, int numPlatosPed) {
    int posPedido = ClienteElegido.cantidadDePedidos; // hice esto por temas de intuitividad

    ClienteElegido.pedidos[posPedido].codigoPedido = codPedido;
    ClienteElegido.pedidos[posPedido].precio = PlatoElegido.precio;
    ClienteElegido.pedidos[posPedido].cantidad = numPlatosPed;
    ClienteElegido.pedidos[posPedido].subtotal = PlatoElegido.precio * numPlatosPed;

    /*
     * observar que aqui estamos igualando punteros de tipo char (apuntan al mismo espacio de memoria)
     * si la cadena se modifica para uno, tambien lo hara para el otro
     * imaginen que el restaurante hace una correcion en la categoria de un plato, el cambio se actualizara automaticamente para cada pedido registrado del mismo plato
     *
     * en este caso, igualar los *char funciona porque queremos que ambos compartan la misma informacion
     * en caso contrario, lo correcto seria asignarle su propio espacio (new char)
     */
    ClienteElegido.pedidos[posPedido].codigoPlato = PlatoElegido.codigo;
    ClienteElegido.pedidos[posPedido].descripcion = PlatoElegido.descripcion;

    ClienteElegido.cantidadDePedidos++;
}

double sumarSubtotales(const struct Cliente &ClienteElegido) {
    double sum = 0;

    for (int i=0; i < ClienteElegido.cantidadDePedidos; i++) {
        sum += ClienteElegido.pedidos[i].subtotal;
    }
    return sum;
}

void imprimirEncabezado(ofstream &archReporte) {
    archReporte << setw(85) << "EMPRESA DE REPARTOS A DOMICILIO TP S. A." << endl;
    archReporte << setw(82) << "RELACION DE PEDIDOS POR CLIENTE" << endl;
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
    char aux[100], *cad;

    arch >> ws;
    arch.getline(aux, 100, delimitador);
    if (arch.eof()) return nullptr;
    arch.clear(); // para casos especiales donde el getline leeria mas de 100 caracteres

    cad = new char[strlen(aux) + 1];
    strcpy(cad, aux);
    return cad;
}

void cambiarClientes(struct Cliente &ClienteI, struct Cliente &ClienteJ) {
    struct Cliente aux = ClienteI;
    ClienteI = ClienteJ;
    ClienteJ = aux;
}

void cambiarPedidos(struct PlatoPedido &PedidoI, struct PlatoPedido &PedidoJ) {
    struct PlatoPedido aux = PedidoI;
    PedidoI = PedidoJ;
    PedidoJ = aux;
}
