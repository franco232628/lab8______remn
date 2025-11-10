//
// Created by GRINGO on 10/11/2025.
//

#ifndef LAB_8_2024_2_AUXILIARYFUNCTIONS_HPP
#define LAB_8_2024_2_AUXILIARYFUNCTIONS_HPP

#include "Utils.hpp"
#include "Distrito.hpp"
#include "PlatoPedido.hpp"
#include "Plato.hpp"
#include "Cliente.hpp"

void leer_distrito(struct Distrito *distrito,
                   int &cant_distrito,
                   const char *file_name);

void open_read(ifstream &input,
               const char *file_name);

char *read_str(ifstream &input, char delim);

void leer_platosOfrecidos(struct Plato *plato,
                          int &cant_plato,
                          const char *file_name);

void leer_cliente(struct Cliente *cliente,
                  int &cant_cliente,
                  const char *file_name);

int read_int(ifstream &input);

double read_double(ifstream &input);

void abrir_clientes(struct Distrito *distrito,
                    int cant_distrito, struct Plato *plato,
                    int cant_plato, struct Cliente *cliente,
                    int cant_cliente,
                    const char *file_name);
int buscarCliente(int dni_leido, struct Cliente * cliente, int cant_cliente);
int buscarPlato(struct Plato * plato, char *codPlato_leido, int cant_plato);
void insertar_pedido( struct Cliente & cliente,
    const struct Plato & plato,
    int cant_pedido_leido,
    int codigo_pedidoleido);
int buscarDistrito(struct Distrito * distrito, int cant_distrito, char * codigo);
double sumar_totales(const struct Cliente & cliente);
void imprimirDistritos(struct Distrito *distritos, int cantDistritos);
void imprimirPlatos(struct Plato *platos, int cantPlatos) ;
void imprimirClientes(struct Cliente *clientes, int cantClientes) ;

#endif //LAB_8_2024_2_AUXILIARYFUNCTIONS_HPP
