#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    ifstream cat;
    ifstream prod;
    ofstream salida;

    if (!abrirArchivos(cat, prod, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    generarReporte(cat, prod, salida);
    cerrarArchivos(cat, prod, salida);

    return 0;
}
