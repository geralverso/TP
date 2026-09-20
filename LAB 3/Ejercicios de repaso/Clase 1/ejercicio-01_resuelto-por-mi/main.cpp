#include <iostream>
#include <fstream>
#include "Bibliotecas/Funciones.h"
using namespace std;

int main() {

    ifstream clientes;
    ifstream pedidos;
    ofstream salida;

    if (!abrirArchivos(clientes, pedidos, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    generarReporte(clientes, pedidos, salida);
    cerrarArchivos(clientes, pedidos, salida);

    return 0;
}
