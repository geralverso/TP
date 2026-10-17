#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    // ------------------------------------------------------------------------------ REPORTE 1:

    int codigosProductos[CAPACIDAD_PRODUCTOS];
    char categoriasProductos[CAPACIDAD_PRODUCTOS];
    int stocksInicialesProductos[CAPACIDAD_PRODUCTOS];
    double preciosUnitProductos[CAPACIDAD_PRODUCTOS];
    int numProductos;

    cargarProductos("ArchivosDeDatos/productos.csv", codigosProductos, categoriasProductos, stocksInicialesProductos,
        preciosUnitProductos,numProductos);
    generarReporteSimple("ArchivosDeReporte/ReporteProductos.txt", codigosProductos, categoriasProductos,
        stocksInicialesProductos, preciosUnitProductos,numProductos);

    // ------------------------------------------------------------------------------ REPORTE 2:

    int totalIngresosProductos[CAPACIDAD_PRODUCTOS]{};
    int totalEgresosProductos[CAPACIDAD_PRODUCTOS]{};
    int stocksFinalesProductos[CAPACIDAD_PRODUCTOS]{};
    double montosTotalesProductos[CAPACIDAD_PRODUCTOS]{};

    leerMovimientos("ArchivosDeDatos/movimientos.txt", codigosProductos, totalIngresosProductos, totalEgresosProductos,
        numProductos);

    armarArregloStocksFinales(stocksFinalesProductos, stocksInicialesProductos, totalIngresosProductos, totalEgresosProductos,
        numProductos);

    armarArregloMontoTotal(montosTotalesProductos, stocksFinalesProductos, preciosUnitProductos, numProductos);

    generarListado("ArchivosDeReporte/productosParaComprar.csv", stocksFinalesProductos, codigosProductos,
        categoriasProductos, numProductos);

    // ------------------------------------------------------------------------------ REPORTE 3:

    ordenarCategoriasYStockFinalConBubble(numProductos, codigosProductos, categoriasProductos, stocksInicialesProductos,
        preciosUnitProductos, totalIngresosProductos, totalEgresosProductos, stocksFinalesProductos, montosTotalesProductos);

    generarReporte("ArchivosDeReporte/kardex.txt", codigosProductos, categoriasProductos, stocksInicialesProductos,
        preciosUnitProductos, totalIngresosProductos, totalEgresosProductos, stocksFinalesProductos, montosTotalesProductos,
        numProductos);

    return 0;
}
