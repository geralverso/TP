#include "Bibliotecas/Funciones.h"

int main() {

    //-----------------------------------------------------------REPORTE 1:

    ifstream espec; //especialidades.csv
    ifstream medicos; //medicos.txt
    ofstream salida; //reporte_especialidades.txt

    if (!abrirArchivos(espec, medicos, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    generarReporte1(espec, medicos, salida);
    cerrarArchivos(espec, medicos, salida);

    //-----------------------------------------------------------REPORTE 2:

    int fechasCitas[CAPACIDAD_CITAS];
    int codigosCitas[CAPACIDAD_CITAS];
    int dnisCitas[CAPACIDAD_CITAS];
    int codigosMedicos[CAPACIDAD_CITAS];
    int numCitas;

    cargarCitas("ArchivosDeDatos/citas.txt", fechasCitas, codigosCitas, dnisCitas, codigosMedicos,numCitas);

    //cout << numCitas << endl;

    ordenarFechasYMedicosConBubble(fechasCitas, codigosCitas, dnisCitas, codigosMedicos, numCitas);

    generarReporte2("ArchivosDeReporte/historial_citas.txt", fechasCitas, codigosCitas, dnisCitas, codigosMedicos,
        numCitas);

    return 0;
}
