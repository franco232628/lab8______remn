#include "MiBiblioteca/FuncionesAux.h"

#define MAX_INFRA 200
#define MAX_EMP 50

int main() {

    struct TablaDeInfracciones arrInfracciones[MAX_INFRA];
    int cantInfracciones;
    LeerTablaInfracciones(arrInfracciones, cantInfracciones);

    struct EmpresaResgitrada arrEmpresas[MAX_EMP];
    int cantEmpresas;
    LeerEmpresas(arrEmpresas, cantEmpresas);

    LeerPlacas(arrEmpresas, cantEmpresas);

    LeerInfracciones(arrEmpresas, cantEmpresas, arrInfracciones, cantInfracciones);

    for (int i=0 ; i<cantEmpresas ; i++) {
        cout<<arrEmpresas[i].nombre<<" ->>>>> ";
        cout<<"Placas: ";
        for (int k=0 ; k<arrEmpresas[i].numPlacas ; k++) {
            cout<<arrEmpresas[i].placas[k]<<" ";
        }
        cout<<endl;
        cout<<"CAnti Multas: "<<arrEmpresas[i].cantidadDeFaltas<<endl;
    }



    return 0;
}