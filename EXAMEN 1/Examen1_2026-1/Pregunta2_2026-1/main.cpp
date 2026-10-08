#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    //ARREGLOS VACIOS
    int codigosMedicos[CAPACIDAD_MEDICOS];
    int codigosEspecialidades[CAPACIDAD_MEDICOS];
    double tarifasMedicos[CAPACIDAD_MEDICOS];
    int cantAtencionesMedicos[CAPACIDAD_MEDICOS];
    int tiempoTotalAtencionesMedicos[CAPACIDAD_MEDICOS];
    int tiempoPromAtencionesMedicos[CAPACIDAD_MEDICOS]{};
    double pagosRecibidosMedicos[CAPACIDAD_MEDICOS]{};
    int numMedicos, numEspecialidades;

    cargarAtenciones("ArchivosDeDatos/Atenciones_TP_Ex1.txt", codigosMedicos, cantAtencionesMedicos,
        tiempoTotalAtencionesMedicos, numMedicos);

    cout << numMedicos << endl;

    generarReportePrueba("ArchivosDeReporte/Reporte_Prueba.txt", codigosMedicos, cantAtencionesMedicos,
        tiempoTotalAtencionesMedicos, numMedicos);

    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cargarEspecialidades("ArchivosDeDatos/Especialidades_Medicos_TP_Ex1.txt", codigosEspecialidades,
        tarifasMedicos,numEspecialidades, codigosMedicos, numMedicos);

    cout << numEspecialidades << endl;

    armarArregloPagos(pagosRecibidosMedicos, numMedicos, tarifasMedicos, tiempoTotalAtencionesMedicos);

    armarArregloTiempoPromedio(tiempoPromAtencionesMedicos, tiempoTotalAtencionesMedicos, numMedicos,
        cantAtencionesMedicos);

    generarReporteAtencionesMedicos("ArchivosDeReporte/Reporte_Atenciones_Medicos.txt", codigosMedicos,
        tarifasMedicos, codigosEspecialidades, cantAtencionesMedicos, tiempoTotalAtencionesMedicos, numMedicos,
        tiempoPromAtencionesMedicos, pagosRecibidosMedicos, 1);

    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    eliminarDatosDeLosArreglos(codigosMedicos, cantAtencionesMedicos, tarifasMedicos, codigosEspecialidades,
        tiempoPromAtencionesMedicos, tiempoTotalAtencionesMedicos, pagosRecibidosMedicos, numMedicos);

    generarReporteAtencionesMedicos("ArchivosDeReporte/Reporte_Atenciones_Medicos_MejorPagados.txt",
        codigosMedicos, tarifasMedicos, codigosEspecialidades, cantAtencionesMedicos, tiempoTotalAtencionesMedicos,
        numMedicos, tiempoPromAtencionesMedicos, pagosRecibidosMedicos, 2);

    return 0;
}
