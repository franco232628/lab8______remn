#include "Bibliotecas/FuncionesAux.h"

#define MAX_STREAM 500
#define MAX_CAT 200

int main() {

    struct Stream arrStreams[MAX_STREAM];
    int cantStreams;
    LeerStreams(arrStreams, cantStreams);

    struct Categoria arrCategorias[MAX_CAT];
    int cantCategorias;
    LeerCategoria(arrCategorias, cantCategorias);

    crearReportes(arrStreams, cantStreams, arrCategorias, cantCategorias);



    return 0;
}