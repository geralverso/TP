#include "Bibliotecas/Funciones.h"

int main() {

    //ARREGLOS VACIOS
    int codigosNotasTeo[CAPACIDAD_TEORIA];
    char secciones[CAPACIDAD_TEORIA];
    double notas_teoricas[CAPACIDAD_TEORIA];
    int codigosNotasPrac[CAPACIDAD_PRACTICA];
    double notas_practica[CAPACIDAD_PRACTICA];
    double notas_finales[CAPACIDAD_TEORIA];
    int numNotasTeoricas, numNotasPracticas; //PARA CALCULAR LAS LONGITUDES

    cargarTeoria("ArchivosDeDatos/teoria.txt", codigosNotasTeo,  secciones, notas_teoricas,
        numNotasTeoricas);
    cargarPractica("ArchivosDeDatos/practica.txt", codigosNotasPrac, notas_practica,
        numNotasPracticas);

    // cout << "numNotasTeoricas= " << numNotasTeoricas << endl;
    // cout << "numNotasPracticas= " << numNotasPracticas << endl;

    generarReporte("ArchivosDeReporte/reporte.txt", codigosNotasTeo, secciones, notas_teoricas,
        numNotasTeoricas, codigosNotasPrac, notas_practica, numNotasPracticas, notas_finales);

    return 0;
}
