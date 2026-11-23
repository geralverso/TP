#include "Bibliotecas/Funciones.h"

int main() {

    struct Nodo *lista;

    crearCatalogo("ArchivosDeDatos/Productos.csv", lista);
    generarReporte("ArchivosDeReporte/ReporteDeProductos.txt", lista, 1);

    agregarProdNuevos("ArchivosDeDatos/ProductosNuevos.csv", lista);
    retirarProductos("ArchivosDeDatos/ProductosRetirados.txt", lista);
    generarReporte("ArchivosDeReporte/ReporteDeCatalogoActualizado.txt", lista, 2);

    cargarVentas("ArchivosDeDatos/Ventas.csv", lista);
    generarReporte("ArchivosDeReporte/ReporteDeVentas.txt", lista, 3);

    eliminarSinVentas(lista);
    generarReporte("ArchivosDeReporte/ReporteFinal.txt", lista, 4);

    liberarMemoria(lista);
    
    return 0;
}
