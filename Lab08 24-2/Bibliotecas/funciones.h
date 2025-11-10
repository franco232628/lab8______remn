//
// Created by Canales Zamora on 09/11/2025.
//

#ifndef TEST16_FUNCIONES_H
#define TEST16_FUNCIONES_H

void cargarDistritos(struct Distrito *arrDistritos, int &cantDistritos);
void cargarPlatos(struct Plato *arrPlatos, int &cantPlatos);
void cargarClientes(struct Cliente *arrClientes, int &cantClientes);
void mostrarReporteSimpleDis(struct Distrito *arrDistritos, int cantDistritos);
void mostrarReporteSimplePla(struct Plato *arrPlatos, int &cantPlatos);
void mostrarReporteSimpleCli(struct Cliente *arrClientes, int cantClientes);
void completarClientes(struct Cliente *arrClientes, int cantClientes, struct Plato *arrPlatos, int cantPlatos, struct Distrito *arrDistritos, int cantDistritos);
void ordenarClientes(struct Cliente *arrClientes, int cantClientes);
void ordenarPedidos(struct Cliente *arrClientes, int cantClientes);
void elaborarReporte(struct Cliente *arrClientes, int cantClientes, struct Plato *arrPlatos, int cantPlatos);
void imprimirPedidos(ofstream &archReporte, struct PlatoPedido *pedidos, int cantPedidos, struct Plato *arrPlatos, int cantPlatos);

int buscarCliente(struct Cliente *arrClientes, int dni, int cantClientes);
int buscarPedido(const struct Cliente &ClienteElegido, int codPedido);
int buscarPlato(struct Plato *arrPlatos, char *codPlato, int cantPlatos);
void insertarPedido(struct Cliente &ClienteElegido, const struct Plato &PlatoElegido, int codPedido, int numPlatosPed);
int buscarDistrito(struct Distrito *arrDistritos, char *codDistrito, int cantDistritos);
double sumarSubtotales(const struct Cliente &ClienteElegido);
void imprimirEncabezado(ofstream &archReporte);

void abrirInput(ifstream &arch, const char* path);
void abrirOutput(ofstream &arch, const char* path);
char* leerCadenaExacta(ifstream &arch, char delimitador);
void cambiarClientes(struct Cliente &ClienteI, struct Cliente &ClienteJ);
void cambiarPedidos(struct PlatoPedido &PedidoI, struct PlatoPedido &PedidoJ);

#endif //TEST16_FUNCIONES_H