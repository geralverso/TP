#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    ifstream atenciones; //Atenciones_TP_Ex1.txt
    ifstream medicos; //Especialidades_Medicos_TP_Ex1.txt
    ifstream pacientes; //Pacientes_TP_Ex1.txt
    ifstream sedes; //Sedes_TP_Ex1.txt
    ofstream salida;

    if (!abrirArchivos(atenciones, medicos, pacientes, sedes, salida)) {
        cout << "No se pudo abrir el archivo de entrada" << endl;
        exit(1);
    }

    generarReporte(atenciones, medicos, pacientes, sedes, salida);

    cerrarArchivos(atenciones, medicos, pacientes, sedes, salida);

    return 0;
}
