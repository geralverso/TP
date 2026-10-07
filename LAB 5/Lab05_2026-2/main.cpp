#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    //ARREGLOS VACIOS:
    int codigosClientes[CAPACIDAD_CLIENTES];
    char tiposDeCreditosClientes[CAPACIDAD_CLIENTES];
    double montosDesembolsadosClientes[CAPACIDAD_CLIENTES];
    int numClientes;

    cargarClientesTXT("ArchivosDeDatos/clientes_registrados.txt", codigosClientes, tiposDeCreditosClientes,
        montosDesembolsadosClientes, numClientes);
    emitirReporteClientes("ArchivosDeReporte/ReporteClientes.txt", codigosClientes, tiposDeCreditosClientes,
        montosDesembolsadosClientes, numClientes);
    ordenarPorCodigoConBurbuja(codigosClientes, tiposDeCreditosClientes, montosDesembolsadosClientes, numClientes);

    // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cargarMovimientosTXT("ArchivosDeDatos/movimientos_clientes.txt", codigosClientes, tiposDeCreditosClientes,
        montosDesembolsadosClientes, numClientes);
    emitirReporteClientesMov("ArchivosDeReporte/ReporteClientesMov.txt", codigosClientes, tiposDeCreditosClientes,
        montosDesembolsadosClientes, numClientes);

    // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //ARREGLOS VACIOS:
    int codigosClientesCuotas[CAPACIDAD_CUOTAS];
    double montosCuotas[CAPACIDAD_CUOTAS];
    double montosPagadosCuotas[CAPACIDAD_CUOTAS];
    int cantDiasDeAtrasoCuotas[CAPACIDAD_CUOTAS];
    int fechasDeVencimientoCuotas[CAPACIDAD_CUOTAS];
    int numCuotas;

    cargarCuotasCSV("ArchivosDeDatos/pagos_cuotas.csv", codigosClientesCuotas, montosCuotas, montosPagadosCuotas,
        cantDiasDeAtrasoCuotas, fechasDeVencimientoCuotas, numCuotas);
    ordenarPorDiasAtrasoConSeleccion(cantDiasDeAtrasoCuotas, codigosClientes, tiposDeCreditosClientes, fechasDeVencimientoCuotas,
        numClientes, codigosClientesCuotas, numCuotas);
    emitirReporteClasificacionCartera("ArchivosDeReporte/ReporteClasificacionCartera.txt", codigosClientesCuotas,
        montosCuotas, montosPagadosCuotas, cantDiasDeAtrasoCuotas, fechasDeVencimientoCuotas, tiposDeCreditosClientes,
        codigosClientes, numCuotas, numClientes);

    return 0;
}
