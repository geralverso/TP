//
// Created by PC on 9/10/2026.
//

#include "Funciones.h"

//-----------------------------------------------------------REPORTE 1:

bool abrirArchivos(ifstream &espec, ifstream &medicos, ofstream &salida) {
    espec.open("ArchivosDeDatos/especialidades.csv");
    medicos.open("ArchivosDeDatos/medicos.txt");
    salida.open("ArchivosDeReporte/reporte_especialidades.txt");
    return espec.is_open() && medicos.is_open() && salida.is_open();
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void leerEImprimirNombres(ifstream &entrada, ofstream &salida) {
    char c;
    while (true) {
        c=entrada.get();
        if (c=='\n' or c==',') break;
        salida << c;
    }
}

void buscarMedicos(ifstream &medicos, ofstream &salida, char letraCodigoEspecialidad, int numCodigoEspecialidad,
    int &cantMedicosPorEspecialidad) {
    int num, codigoMedico;
    char letra;
    medicos.clear();
    medicos.seekg(0);
    while (medicos >> codigoMedico) {
        while (medicos.peek()!='\n') {
            if (medicos >> letra >> num) {
                if (letra==letraCodigoEspecialidad and num==numCodigoEspecialidad) {
                    salida << codigoMedico << " ";
                    cantMedicosPorEspecialidad++;
                }
            }
            else {
                medicos.clear();
                break;
            }
        }
    }
}

void generarReporte1(ifstream &espec, ifstream &medicos, ofstream &salida) {
    //ENCABEZADO
    salida << "REPORTE DE MEDICOS POR ESPECIALIDAD" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE1);

    int numCodigoEspecialidad, cantEspecialidades=0, cantMedicos=0;
    double precio;
    char c, letraCodigoEspecialidad;
    while (espec >> letraCodigoEspecialidad >> numCodigoEspecialidad >> c) {
        cantEspecialidades++;
        salida << left << setw(13) << "Especialidad" << ": " << letraCodigoEspecialidad << right << setw(2)
                << setfill('0') << numCodigoEspecialidad << setfill(' ') << endl;
        salida << left << setw(13) << "Descripcion" << ": ";
        leerEImprimirNombres(espec, salida);
        espec >> precio;
        salida << "\n" << left << setw(13) << "Precio" << ": " << fixed << setprecision(2) << precio << endl;
        salida << left << setw(13) << "Medicos" << ": ";

        int cantMedicosPorEspecialidad=0;
        //USAMOS UNA FUNCION DE BUSQUEDA
        buscarMedicos(medicos, salida, letraCodigoEspecialidad, numCodigoEspecialidad, cantMedicosPorEspecialidad);
        salida << "\n" << left << setw(13) << "Resumen" << ": " << cantMedicosPorEspecialidad << " medico(s) en la especialidad" << endl;
        imprimirSeparador(salida, '-', ANCHO_REPORTE1);
        cantMedicos+=cantMedicosPorEspecialidad;
    }
    salida << "Total de especialidades: " << cantEspecialidades << endl;
    salida << "Total de asignaciones medico-especialidad: " << cantMedicos << endl;
}

void cerrarArchivos(ifstream &espec, ifstream &medicos, ofstream &salida) {
    espec.close();
    medicos.close();
    salida.close();
}

//-----------------------------------------------------------REPORTE 2:

void cargarCitas(const char *nombreArchivo, int *fechasCitas, int *codigosCitas, int *dnisCitas, int *codigosMedicos,
    int &numCitas) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numCitas=0;
    char c;
    int fecha, codigoCita, dni, codigoMedico, dia, mes, anio;
    while (entrada >> codigoCita) {
        entrada >> dni >> codigoMedico >> dia >> c >> mes >> c >> anio;
        fecha=(anio*10000)+(mes*100)+dia;
        codigosCitas[numCitas]=codigoCita;
        dnisCitas[numCitas]=dni;
        codigosMedicos[numCitas]=codigoMedico;
        fechasCitas[numCitas]=fecha;
        numCitas++;
    }
}

void imprimirEncabezado(ofstream &salida) {
    salida << "HISTORIAL DE CITAS\n" << "(ordenado por fecha y luego por medico)" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE2);
    salida << left << setw(12) << "Fecha" << setw(7) << "Cita" << setw(11) << "DNI" << setw(6) << "Medico" << endl;
}

void imprimirFecha(int fecha, ofstream &salida) {
    int anio=fecha/10000, mes=(fecha%10000)/100, dia=fecha%100;
    salida << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/" << setw(4) << anio
            << setfill(' ') << setw(2) << "";
}

void intercambiarInt(int &a, int &b) {
    int aux=a;
    a=b, b=aux;
}

void ordenarFechasYMedicosConBubble(int *fechasCitas, int *codigosCitas, int *dnisCitas, int *codigosMedicos,
    int numCitas) {
    //ORDENACION ASCENDENTE (MENOR A MAYOR)
    for (int i=0; i<(numCitas-1); i++) {
        for (int j=0; j<numCitas-1-i; j++) {
            if (fechasCitas[j]>fechasCitas[j+1] or
                (fechasCitas[j]==fechasCitas[j+1] and codigosMedicos[j]>codigosMedicos[j+1])) {
                intercambiarInt(fechasCitas[j],fechasCitas[j+1]);
                intercambiarInt(codigosCitas[j],codigosCitas[j+1]);
                intercambiarInt(dnisCitas[j],dnisCitas[j+1]);
                intercambiarInt(codigosMedicos[j],codigosMedicos[j+1]);
            }
        }
    }
}

void generarReporte2(const char *nombreArchivo, int *fechasCitas, int *codigosCitas, int *dnisCitas, int *codigosMedicos,
    int numCitas) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    imprimirEncabezado(salida);
    for (int i = 0; i < numCitas; i++) {
        int fecha=fechasCitas[i];
        int cita=codigosCitas[i];
        int dni=dnisCitas[i];
        int medico=codigosMedicos[i];

        imprimirFecha(fecha,salida);
        salida << left << setw(7) << cita << setw(11) << dni << setw(6) << medico << endl;
    }
    imprimirSeparador(salida, '-', ANCHO_REPORTE2);
    salida << "Total de citas: " << numCitas;
}
