#include "Bibliotecas/Funciones.h"

int main() {

    struct Vehiculo *vehiculos;
    int numVehiculos;
    cargarVehiculos("ArchivosDeDatos/vehiculos_registrados.txt", vehiculos, numVehiculos);
    generarReporte("ArchivosDeReporte/reporteInicial.txt", vehiculos, numVehiculos);
    cargarCapturas("ArchivosDeDatos/capturas_camaras.csv", vehiculos, numVehiculos);
    generarReporte("ArchivosDeReporte/reporteCapturas.txt", vehiculos, numVehiculos);
    identificarInfracciones(vehiculos, numVehiculos);
    generarReporte("ArchivosDeReporte/reporteInfracciones.txt", vehiculos, numVehiculos);
    ordenarVehiculos(vehiculos, numVehiculos);
    generarReporte("ArchivosDeReporte/reporteInfraccionesOrdenado.txt", vehiculos, numVehiculos);

    return 0;
}
