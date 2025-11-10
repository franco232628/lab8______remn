//
// Created by Canales Zamora on 09/11/2025.
//

#ifndef TEST16_CLIENTE_H
#define TEST16_CLIENTE_H

// observar que en esta estructura se forma un arreglo con su respectivo contador
struct Cliente {
    int dni, cantidadDePedidos; // cantPedidos -> arrPedidos
    double montoTotal;
    char *nombre;
    struct Distrito distrito;
    struct PlatoPedido pedidos[30]; // ningun cliente tiene mas de 30 pedidos segun el enunciado
};

#endif //TEST16_CLIENTE_H