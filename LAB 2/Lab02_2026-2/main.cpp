#include <iostream>
#include <fstream>
#include "Bibliotecas/Funciones.h"
using namespace std;

int main() {

    // 1 ENTRADA : 2 SALIDAS
    ifstream entrada; //<---lecturas_sensores_planta.txt
    ofstream estadisticas; //<---estadisticas_sensores.txt
    ofstream alertas; //<---alertas_sensores.txt

    if (!abrirArchivos(entrada, estadisticas, alertas)) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    int ddi=7, mmi=9, aai=2026;
    int ddf=9, mmf=9, aaf=2026;

    generarEstadisticasYAlertas(entrada, alertas, estadisticas, ddi, mmi, aai, ddf, mmf, aaf);
    cerrarArchivos(entrada, estadisticas, alertas);

    return 0;
}
