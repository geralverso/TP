#include "Bibliotecas/Funciones.h"

int main() {

    //ARREGLOS VACIOS DE nuevos.csv
    int codigosNuevos[CAPACIDAD_NUEVOS];
    char categoriasDeNuevos[CAPACIDAD_NUEVOS];
    double preciosNuevos[CAPACIDAD_NUEVOS];
    int stocksNuevos[CAPACIDAD_NUEVOS];
    bool importadosNuevos[CAPACIDAD_NUEVOS];
    int numNuevos;

    //ARREGLOS VACIOS DE productos.csv
    int codigosProductos[CAPACIDAD_PRODUCTOS];
    char categoriasDeProductos[CAPACIDAD_PRODUCTOS];
    double preciosProductos[CAPACIDAD_PRODUCTOS];
    int stocksProductos[CAPACIDAD_PRODUCTOS];
    bool importadosProductos[CAPACIDAD_PRODUCTOS];
    int numProductos;

    cargarNuevosCSV("ArchivosDeDatos/nuevos.csv", codigosNuevos, categoriasDeNuevos, preciosNuevos,
        stocksNuevos, importadosNuevos, numNuevos);

    cargarProductosCSV("ArchivosDeDatos/productos.csv", codigosProductos, categoriasDeProductos,
        preciosProductos, stocksProductos, importadosProductos, numProductos);

    generarReporte("ArchivosDeReporte/reporte.txt", codigosNuevos, categoriasDeNuevos, preciosNuevos,
        stocksNuevos, importadosNuevos, numNuevos, codigosProductos, categoriasDeProductos,preciosProductos,
        stocksProductos, importadosProductos,  numProductos);

    // cout << numNuevos << endl;
    // cout << numProductos << endl;

    return 0;
}
