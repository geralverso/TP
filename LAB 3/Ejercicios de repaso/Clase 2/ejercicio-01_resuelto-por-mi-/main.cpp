#include <iostream>
#include "Bibliotecas/Funciones.h"
using namespace std;
#include <fstream>

int main() {

    ifstream movi; //movimientos.csv
    ifstream prod; //productos.csv
    ofstream salida;

    if (!abrirArchivos(movi, prod, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    generarReporte(movi, prod, salida);
    cerrarArchivos(movi, prod, salida);

    return 0;
}
