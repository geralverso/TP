#include "Bibliotecas/Funciones.h"

int main() {

    struct Nodo* lista;
    struct Resumen resumen{};
    struct TotalPorZona totalPorZona{};

    cargarEnvios("ArchivosDeDatos/Envios.csv", lista, resumen);

    procesarClientes("ArchivosDeDatos/Clientes.csv", lista);

    procesarDestinos("ArchivosDeDatos/Distritos.csv", lista, resumen);

    generarReporte("ArchivosDeReporte/ReporteDeEnvios.txt", lista, resumen, totalPorZona);

    eliminarSinCobertura(lista, "(sin cobertura)");


    registrarEntregas("ArchivosDeDatos/Entregas.csv", lista, resumen);

    calcularCostos(lista);

    generarReporte("ArchivosDeReporte/ReporteFinal.txt", lista, resumen, totalPorZona);




    return 0;
}
