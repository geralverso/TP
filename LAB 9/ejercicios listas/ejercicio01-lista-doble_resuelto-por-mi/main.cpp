#include "Bibliotecas/Funciones.h"

int main() {

    struct NodoDoble *lista;

    cargarNumeros("ArchivosDeDatos/numeros.txt", lista);

    generarReporte("ArchivosDeReporte/reporte.txt", lista);

    eliminarDeLaLista(lista, 33);

    eliminarMenores(lista, 10);

    generarReporte("ArchivosDeReporte/reporteConElementosEliminados.txt", lista);

    eliminarLista(lista);

    return 0;
}
