#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.h"
using namespace std;
#include <fstream>

int main() {

    ifstream entrada;
    ofstream salida;

    if (!abrirArchivos(entrada, salida)) {
        cout << "No se puede abrir el archivo." << endl;
        return 1;
    }

    int diaReferencial=7,mesReferencial=9, anioReferencial=2026;
    generarReporte(entrada, salida, diaReferencial,mesReferencial, anioReferencial);
    cerrarArchivos(entrada, salida);

    return 0;
}
