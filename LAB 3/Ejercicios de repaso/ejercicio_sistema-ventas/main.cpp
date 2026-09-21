#include <iostream>
#include <fstream>
#include "Bibliotecas/Funciones.h"
using namespace std;

int main() {

    ifstream ventas; //ventas.csv
    ifstream inven; //inventario.txt
    ifstream config; //config_tienda.json
    ofstream txt; //reporte_ventas.txt <--1RA SALIDA
    ofstream json; //reporte_ventas.json <--2DA SALIDA
    ofstream csv; //reporte_ventas.csv <--3RA SALIDA

    if (!abrirArchivos(ventas, inven, config, txt, json, csv)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    generarReportes(ventas, inven, config, txt, json, csv);
    cerrarArchivos(ventas, inven, config, txt, json, csv);

    return 0;
}
