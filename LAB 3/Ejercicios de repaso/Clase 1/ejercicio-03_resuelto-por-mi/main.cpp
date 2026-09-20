#include <iostream>
#include <fstream>

#include "Bibliotecas/Funciones.h"
using namespace std;

int main() {

    //  ENTRADA          SALIDA
    // 1) ventas.csv -> ventas.json (PRIMERO TRASFORMAREMOS .csv A .json)

    ifstream csv;
    ofstream json;

    if (!abrirArchivos1(csv, json)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    generarReporteJSON(csv, json);
    cerrarArchivos1(csv, json);

    ////////////////////////////////////////////////////////////////////////////////////////////

    //  ENTRADA          SALIDA
    // 2) ventas.json -> reporte.txt (AHORA TRASFORMAREMOS .json A .txt)

    ifstream entrada; //ahora json es entrada
    ofstream salida;

    if (!abrirArchivos2(entrada, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    generarReporteTXT(entrada, salida);
    cerrarArchivos2(entrada, salida);

    return 0;
}
