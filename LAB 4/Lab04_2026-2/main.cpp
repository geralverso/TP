#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    //ARREGLOS VACIOS PARA vehiculos_registrados.txt
    int codigosVehiculos[CAPACIDAD_VEHICULOS];        //SOLO ESTOS 2 ARREGLOS SE VAN A USAR
    char categoriasVehiculos[CAPACIDAD_VEHICULOS];
    int numVehiculos;

    //ARREGLOS VACIOS PARA capturas_camaras.csv
    int codigosVehiculosCapturas[CAPACIDAD_CAPTURAS];
    double velocidadesCapturas[CAPACIDAD_CAPTURAS];
    int carrilesCapturas[CAPACIDAD_CAPTURAS];
    int kilometrosCapturas[CAPACIDAD_CAPTURAS];
    int diasCapturas[CAPACIDAD_CAPTURAS];
    int mesCapturas[CAPACIDAD_CAPTURAS];
    int aniosCapturas[CAPACIDAD_CAPTURAS];
    int codigosCamarasCapturas[CAPACIDAD_CAPTURAS];
    int numCapturas;

    double montoInfraccM[CAPACIDAD_CAPTURAS]{};
    double montoInfraccG[CAPACIDAD_CAPTURAS]{};

    cargarVehiculosTXT("ArchivosDeDatos/vehiculos_registrados.txt", codigosVehiculos, categoriasVehiculos,
        numVehiculos);
    cargarCapturasCSV("ArchivosDeDatos/capturas_camaras.csv", codigosVehiculosCapturas, velocidadesCapturas,
        carrilesCapturas, kilometrosCapturas, diasCapturas, mesCapturas, aniosCapturas, codigosCamarasCapturas,
        numCapturas);

    // cout << numVehiculos << endl;
    // cout << numCapturas << endl;

    generarReportes("ArchivosDeReporte/reporte_infracciones.txt","ArchivosDeReporte/lecturas_invalidas.csv",
        codigosVehiculos, categoriasVehiculos, numVehiculos, codigosVehiculosCapturas, velocidadesCapturas, carrilesCapturas,
        kilometrosCapturas, diasCapturas, mesCapturas, aniosCapturas, codigosCamarasCapturas, numCapturas, montoInfraccM,
        montoInfraccG);

    return 0;
}
