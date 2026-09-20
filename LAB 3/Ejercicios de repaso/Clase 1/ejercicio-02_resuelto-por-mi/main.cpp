#include <iostream>

#include "Bibliotecas/Funciones.h"
using namespace std;
#include <fstream>

int main() {

    ifstream entrada;
    ofstream salida;

    if (!abrirArchivos(entrada, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    generarReporte(entrada,salida);
    cerrarArchivos(entrada, salida);

    return 0;
}
