//
// Created by GRINGO on 10/11/2025.
//

#ifndef LAB_8_2024_2_CLIENTE_HPP
#define LAB_8_2024_2_CLIENTE_HPP
#include "Distrito.hpp"
#include "PlatoPedido.hpp"

struct Cliente {
    int dni;
    char *nombre;
    struct Distrito distrito;
    struct PlatoPedido pedidos[30];//
    int cantidadDePedidos;//
    double montoTotal;
};

#endif //LAB_8_2024_2_CLIENTE_HPP