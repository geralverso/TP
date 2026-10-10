#include "Bibliotecas/Funciones.h"

int main() {

    // ----------------------------------------------------- REPORTE 1:

    ifstream planes; //planes.txt
    ifstream usuarios; //usuarios.csv
    ifstream llamadas; //llamadas.txt
    ofstream salida; //reporte_llamadas_usuarios.txt

    if (!abrirArchivos(planes, usuarios, llamadas, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    generarReporte1(planes, usuarios, llamadas, salida);

    cerrarArchivos(planes, usuarios, llamadas, salida);


    // ----------------------------------------------------- REPORTE 2:

    int dnisUsuarios[CAPACIDAD_USUARIOS];
    int telefonosUsuarios[CAPACIDAD_USUARIOS];
    int cantLlamadasUsuarios[CAPACIDAD_USUARIOS]{};
    int duracionTotalLlamadas[CAPACIDAD_USUARIOS]{};
    int fechaUltimasLlamadas[CAPACIDAD_USUARIOS]{};
    int numUsuarios, numLlamadas;

    cargarUsuarios("ArchivosDeDatos/usuarios.csv", dnisUsuarios, telefonosUsuarios, numUsuarios);

    cargarLlamadas("ArchivosDeDatos/llamadas.txt", telefonosUsuarios, numUsuarios, cantLlamadasUsuarios,
        duracionTotalLlamadas, fechaUltimasLlamadas, numLlamadas);

    generarReporte2("ArchivosDeReporte/listado_llamadas_usuarios.txt", dnisUsuarios, telefonosUsuarios,
        numUsuarios, cantLlamadasUsuarios, duracionTotalLlamadas, fechaUltimasLlamadas, numLlamadas);

    return 0;
}
