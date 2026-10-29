#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    int resultadosTelefono[CAP_RESULTADOS_TELEFONO]{};
    int resultadosCorreo[CAP_RESULTADOS_CORREO]{};
    int resultadosContrasena[CAP_RESULTADOS_CONTRASENA]{};

    cargarYValidarDatos("ArchivosDeDatos/datos.csv", "ArchivosDeReporte/DatosValidos.txt",
        resultadosTelefono, resultadosCorreo, resultadosContrasena);

    generarReporte("ArchivosDeReporte/Reporte.txt", resultadosTelefono, resultadosCorreo, resultadosContrasena);

    return 0;
}
