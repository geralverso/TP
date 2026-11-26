#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    struct Plato* plato;
    leerPlatos("ArchivosDeDatos/Platos.csv", plato);

    struct Distrito* distrito;
    leerDistritos("ArchivosDeDatos/Distritos.csv", distrito);

    struct Nodo* lista;
    leerPedidos("ArchivosDeDatos/Pedidos.csv", lista, plato, distrito);

    generarReporte1("ArchivosDeReporte/ReporteDePedidosRecibidos.txt", lista);

    int horaL=22, minL=30, segL=0;
    eliminarPedidos(lista, horaL, minL, segL);
    generarReporte2("ArchivosDeReporte/ReporteDePedidosADespachar.txt", lista, horaL, minL, segL);

    eliminarLista(lista, distrito);

    return 0;
}
