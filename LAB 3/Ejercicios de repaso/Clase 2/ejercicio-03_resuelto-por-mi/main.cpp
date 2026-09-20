#include <iostream>
#include <fstream>

#include "Bibliotecas/Funciones.h"
using namespace std;

int main() {

    ifstream csv;
    ofstream json;
    if (!abrirArchivos1(csv, json)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    generarJSON(csv, json);
    cerrarArchivos1(csv, json);

    ifstream entrada; //ahora json es entrada
    ofstream salida;
    if (!abrirArchivos2(entrada, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    generarTXT(entrada, salida);
    cerrarArchivos2(entrada, salida);

    return 0;
}
