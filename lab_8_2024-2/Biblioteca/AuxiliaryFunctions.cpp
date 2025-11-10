//
// Created by GRINGO on 10/11/2025.
//

#include "AuxiliaryFunctions.hpp"

void open_read(ifstream &input, const char *file_name) {
    input.open(file_name, ios::in);
    if (!input.is_open()) {
        cout << "Error opening file " << file_name << endl;
        exit(1);
    }
}

int buscarCliente(int dni_leido, struct Cliente *cliente, int cant_cliente) {
    for (int i = 0; i < cant_cliente; i++) {
        if (cliente[i].dni == dni_leido) {
            return i;
        }
    }
    return -1;
}

int buscarPlato(struct Plato *plato, char *codPlato_leido, int cant_plato) {
    for (int i = 0; i < cant_plato; i++) {
        if (strcmp(codPlato_leido, plato[i].codigo) == 0) {
            return i;
        }
    }
    return -1;
}

char *read_str(ifstream &input, char delim) {
    char buffer[100], *str;
    input.getline(buffer, 100, delim);
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}


int read_int(ifstream &input) {
    int i;
    input >> i;
    input.get();
    return i;
}

double read_double(ifstream &input) {
    double i;
    input >> i;
    input.get();
    return i;
}




void leer_distrito(struct Distrito *distrito,
                   int &cant_distrito,
                   const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    struct Distrito c;
    char *codigo_leido;
    while (true) {
        //LN3085,Ancon,NORTE
        codigo_leido = read_str(input, ',');
        if (input.eof()) break;
        c.codigo = codigo_leido;
        c.nombre = read_str(input, ',');
        c.ubicacion = read_str(input, '\n');

        distrito[cant_distrito] = c;
        cant_distrito++;
    }
}


void leer_platosOfrecidos(struct Plato *plato,
                          int &cant_plato,
                          const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    struct Plato c;
    char *codigo_leido;
    while (true) {
        //PO-11283,2 BOLAS DE HELADO,14.90,POSTRES
        codigo_leido = read_str(input, ',');
        if (input.eof()) break;
        c.codigo = codigo_leido;
        c.descripcion = read_str(input, ',');
        c.precio = read_double(input);
        c.categoria = read_str(input, '\n');
        plato[cant_plato] = c;
        cant_plato++;
    }
}

void leer_cliente(struct Cliente *cliente,
                  int &cant_cliente,
                  const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    struct Cliente c;
    int dni_leido;
    char *codigo_leido;
    while (true) {
        //90367684,CORONEL CHUMPITAZ HELI,LS8594
        dni_leido = read_int(input);
        if (input.eof()) break;
        c.dni = dni_leido;
        c.nombre= read_str(input, ',');
        c.distrito.codigo = read_str(input, '\n');
        c.cantidadDePedidos = 0;
        cliente[cant_cliente] = c;
        cant_cliente++;
        // cliente[cant_cliente].cantidadDePedidos =0;
        // cliente[cant_cliente].montoTotal = 0;
    }

}




void abrir_clientes(struct Distrito *distrito,
                    int cant_distrito,
                    struct Plato *plato,
                    int cant_plato,
                    struct Cliente *cliente,
                    int cant_cliente,
                    const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    int codigo_Pedidoleido, dni_leido, cant_pedido_leido;
    char codPlato_leido[10];
    while (true) {
        //117660      68114999        AP-73428       3
        input >> codigo_Pedidoleido;
        if (input.eof()) break;
        input >> dni_leido >> ws >> codPlato_leido >> ws>> cant_pedido_leido;
        // cout << codigo_Pedidoleido<<"  -  " << dni_leido <<"  -  "
        //         << codPlato_leido <<"  -  " << cant_pedido_leido << endl;
        int posCliente = buscarCliente(dni_leido, cliente, cant_cliente);
        int posPlato = buscarPlato(plato, codPlato_leido, cant_plato);
        if (posCliente != -1 and posPlato != -1) {
            insertar_pedido(cliente[posCliente],
                plato[posPlato], cant_pedido_leido,
                codigo_Pedidoleido );
        }
        // for (int i = 0; i < cant_cliente; i++) {
        //     int posDistrito = buscarDistrito(distrito, cant_distrito, cliente[i].distrito.codigo);
        //     if (posDistrito != -1) {
        //         delete cliente[i].distrito.codigo; // este es un añadido personal para despejar el espacio asignado a la copia almacenada de codDistrito en Clientes.csv
        //         cliente[i].distrito = distrito[posDistrito];
        //     }
        //     cliente[i].montoTotal = sumar_totales(cliente[i]);
        // }

    }
}
int buscarDistrito(struct Distrito *distrito, int cant_distrito, char *codigo) {
    for (int i = 0; i < cant_distrito; i++) {
        if (strcmp(distrito[i].codigo, codigo) == 0) return i;
    }
    return -1;
}

double sumar_totales(const struct Cliente &cliente) {
    double sum = 0;

    for (int i=0; i < cliente.cantidadDePedidos; i++) {
        sum += cliente.pedidos[i].subtotal;
    }
    return sum;
}

//
// void insertar_pedido( struct Cliente &cliente, const struct Plato &plato, int cant_pedido_leido,
//                       int codigo_pedidoleido) {
//     int posPedido = cliente.cantidadDePedidos;
//     cout << posPedido<< endl;
//     cliente.pedidos[posPedido].codigoPedido = codigo_pedidoleido;
//     cliente.pedidos[posPedido].precio = plato.precio;
//     cliente.pedidos[posPedido].cantidad =cant_pedido_leido;
//     cliente.pedidos[posPedido].subtotal =cant_pedido_leido*plato.precio;
//
//     cliente.pedidos[posPedido].codigoPlato =plato.codigo;
//     cliente.pedidos[posPedido].descripcion =plato.descripcion;
//
//     cliente.cantidadDePedidos++;
// }

void insertar_pedido(struct Cliente &cliente, const struct Plato &plato,
                     int cant_pedido_leido, int codigo_pedidoleido) {
    const int MAX_PEDIDOS = 30; // límite definido en el struct

    if (cliente.cantidadDePedidos >= MAX_PEDIDOS) {
        cout << "Error: el cliente " << cliente.dni << " excede el límite de pedidos." << endl;
        return;
    }

    int posPedido = cliente.cantidadDePedidos;

    // Asignar datos básicos
    cliente.pedidos[posPedido].codigoPedido = codigo_pedidoleido;
    cliente.pedidos[posPedido].cantidad = cant_pedido_leido;
    cliente.pedidos[posPedido].precio = plato.precio;
    cliente.pedidos[posPedido].subtotal = plato.precio * cant_pedido_leido;

    // Copias profundas de los punteros char*
    cliente.pedidos[posPedido].codigoPlato = new char[strlen(plato.codigo) + 1];
    strcpy(cliente.pedidos[posPedido].codigoPlato, plato.codigo);

    cliente.pedidos[posPedido].descripcion = new char[strlen(plato.descripcion) + 1];
    strcpy(cliente.pedidos[posPedido].descripcion, plato.descripcion);

    cliente.cantidadDePedidos++;

    // Actualiza el monto total del cliente
    cliente.montoTotal += cliente.pedidos[posPedido].subtotal;
}



void imprimirDistritos(struct Distrito *distritos, int cantDistritos) {
    cout << "\n===== LISTA DE DISTRITOS =====\n";
    for (int i = 0; i < cantDistritos; i++) {
        cout << "[" << i + 1 << "] "
             << distritos[i].codigo << " | "
             << distritos[i].nombre << " | "
             << distritos[i].ubicacion << endl;
    }
}

// -------------------- IMPRIMIR PLATOS --------------------
void imprimirPlatos(struct Plato *platos, int cantPlatos) {
    cout << "\n===== LISTA DE PLATOS =====\n";
    for (int i = 0; i < cantPlatos; i++) {
        cout << "[" << i + 1 << "] "
             << platos[i].codigo << " | "
             << platos[i].descripcion << " | "
             << fixed << setprecision(2)
             << platos[i].precio << " | "
             << platos[i].categoria << endl;
    }
}

// -------------------- IMPRIMIR CLIENTES --------------------
void imprimirClientes(struct Cliente *clientes, int cantClientes) {
    cout << "\n===== LISTA DE CLIENTES =====\n";
    for (int i = 0; i < cantClientes; i++) {
        cout << "\nCliente " << i + 1 << ": "
             << clientes[i].nombre << " (DNI " << clientes[i].dni << ")\n"
             << "Distrito: " << clientes[i].distrito.codigo << "\n"
             << "Pedidos realizados: " << clientes[i].cantidadDePedidos << endl;

        // imprimir sus pedidos
        if (clientes[i].cantidadDePedidos > 0) {
            cout << "  --- Pedidos ---\n";
            for (int j = 0; j < clientes[i].cantidadDePedidos; j++) {
                cout << "   Pedido " << j + 1 << ": "
                     << "CodPedido " << clientes[i].pedidos[j].codigoPedido
                     << ", Plato " << clientes[i].pedidos[j].codigoPlato
                     << " (" << clientes[i].pedidos[j].descripcion << ")"
                     << ", Cantidad: " << clientes[i].pedidos[j].cantidad
                     << ", Subtotal: S/ "
                     << fixed << setprecision(2)
                     << clientes[i].pedidos[j].subtotal << endl;
            }
        }
        cout << "Monto total del cliente: S/ "
             << fixed << setprecision(2) << clientes[i].montoTotal << endl;
    }
}
