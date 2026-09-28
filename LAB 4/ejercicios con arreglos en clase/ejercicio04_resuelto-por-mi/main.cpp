#include "Bibliotecas/Funciones.h"

int main() {

    //ARREGLOS VACIOS EN consultas.txt
    int codigosConsultas[CAPACIDAD_CONSULTAS];
    int numConsultas;

    //ARREGLOS VACIOS EN categorias.txt
    char categoriasEnCategorias[CAPACIDAD_CATEGORIAS];
    int numCategorias;

    //ARREGLOS VACIOS EN productos.csv
    int codigosProductos[CAPACIDAD_PRODUCTOS];
    char categoriasProductos[CAPACIDAD_PRODUCTOS];
    double preciosProductos[CAPACIDAD_PRODUCTOS];
    int stocksProductos[CAPACIDAD_PRODUCTOS];
    bool importadosProductos[CAPACIDAD_PRODUCTOS];
    int numProductos;

    cargarConsultasTXT("ArchivosDeDatos/consultas.txt", codigosConsultas, numConsultas);

    cargarCategoriasTXT("ArchivosDeDatos/categorias.txt", categoriasEnCategorias, numCategorias);

    cargarProductosCSV("ArchivosDeDatos/productos.csv", codigosProductos, categoriasProductos,
         preciosProductos, stocksProductos, importadosProductos, numProductos);

    // cout << numConsultas << endl;
    // cout << numCategorias << endl;
    // cout << numProductos << endl;

    generarReporte("ArchivosDeReporte/reporte.txt", codigosConsultas, numConsultas, categoriasEnCategorias,
        numCategorias, codigosProductos, categoriasProductos,preciosProductos, stocksProductos, importadosProductos,
        numProductos);

    return 0;
}
