#include "Bibliotecas/Funciones.h"

int main() {

    //ARREGLOS VACIOS PARA ventas.csv
    int codigosVentas[CAPACIDAD];
    int cantidadesVentas[CAPACIDAD];
    int numVentas;

    //ARREGLOS VACIOS PARA productos.csv
    int codigosProductos[CAPACIDAD];
    char categoriasProductos[CAPACIDAD];
    double preciosProductos[CAPACIDAD];
    int stocksProductos[CAPACIDAD];
    bool importadosProductos[CAPACIDAD];
    int numProductos;

    int cantProductosVendidos[CAPACIDAD]{};
    double ingresoProductosVendidos[CAPACIDAD]{};

    cargarVentasCSV("ArchivosDeDatos/ventas.csv", codigosVentas, cantidadesVentas, numVentas);
    cargarProductosCSV("ArchivosDeDatos/productos.csv", codigosProductos, categoriasProductos,
        preciosProductos, stocksProductos, importadosProductos, numProductos);

    // cout << numVentas << endl;
    // cout << numProductos << endl;

    generarReporte("ArchivosDeReporte/reporte.txt", codigosVentas, cantidadesVentas, numVentas,
        codigosProductos, preciosProductos, stocksProductos, numProductos, cantProductosVendidos,
        ingresoProductosVendidos);

    return 0;
}
