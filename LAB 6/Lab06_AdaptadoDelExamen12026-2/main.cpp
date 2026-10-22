#include "Bibliotecas/Funciones.h"

int main() {

    //ESTO RESPONDE A LA PREGUNTA 3 DEL EX1 2026-2

    char* categorias;
    int* codigosProductos;
    int* stocksIniciales;
    double* preciosUnitarios;
    int numProductos;

    cargarProductos("ArchivosDeDatos/productos.csv", categorias, codigosProductos, stocksIniciales,
        preciosUnitarios, numProductos);

    generarReporteSimple("ArchivosDeReporte/ReporteProductos.txt", categorias, codigosProductos, stocksIniciales,
        preciosUnitarios, numProductos);

    int* totalIngresos;
    int* totalEgresos;
    int* stocksFinales;
    double* montosTotales;

    cargarMovimientos("ArchivosDeDatos/movimientos.txt", codigosProductos, totalIngresos, totalEgresos,
        numProductos);

    armarStocksFinales(stocksFinales, stocksIniciales, totalIngresos, totalEgresos, numProductos);

    armarMontosTotales(montosTotales, preciosUnitarios, stocksFinales, numProductos);

    generarListado("ArchivosDeReporte/productosParaComprar.csv", categorias, codigosProductos, numProductos,
        stocksFinales);

    ordenarCatYStockFinalPorSeleccion(categorias, codigosProductos, stocksIniciales, totalIngresos, totalEgresos,
        preciosUnitarios, stocksFinales, montosTotales, numProductos);

    generarReporte("ArchivosDeReporte/kardex.txt", categorias, codigosProductos, stocksIniciales, totalIngresos,
        totalEgresos, preciosUnitarios, stocksFinales, montosTotales, numProductos);

    delete[] categorias;
    delete[] codigosProductos;
    delete[] stocksIniciales;
    delete[] totalIngresos;
    delete[] totalEgresos;
    delete[] stocksFinales;
    delete[] preciosUnitarios;
    delete[] montosTotales;

    return 0;
}
