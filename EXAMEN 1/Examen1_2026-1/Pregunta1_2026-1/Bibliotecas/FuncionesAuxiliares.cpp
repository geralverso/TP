//
// Created by PC on 7/10/2026.
//

#include "FuncionesAuxiliares.h"

bool abrirArchivos(ifstream &atenciones, ifstream &medicos, ifstream &pacientes, ifstream &sedes, ofstream &salida) {
    atenciones.open("ArchivosDeDatos/Atenciones_TP_Ex1.txt");
    medicos.open("ArchivosDeDatos/Especialidades_Medicos_TP_Ex1.txt");
    pacientes.open("ArchivosDeDatos/Pacientes_TP_Ex1.txt");
    sedes.open("ArchivosDeDatos/Sedes_TP_Ex1.txt");
    salida.open("ArchivosDeReporte/Reporte.txt");
    return atenciones.is_open() and medicos.is_open() and pacientes.is_open() and sedes.is_open() and salida.is_open();
}

void cerrarArchivos(ifstream &atenciones, ifstream &medicos, ifstream &pacientes, ifstream &sedes, ofstream &salida) {
    atenciones.close();
    medicos.close();
    pacientes.close();
    sedes.close();
    salida.close();
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void imprimirEncabezado(ofstream &salida) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << right << setw((ANCHO_REPORTE+29)/2) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    salida << right << setw((ANCHO_REPORTE+19)/2) << "ATENCIONES POR SEDE" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}

void leerImprimirNombres(ifstream &entrada, ofstream &salida, int anchoColumna, bool seMuestra) {
    char c;
    int cantCaracteres=0;
    while (true) {
        c=entrada.get();
        if (c==' ' or c=='\n') break;
        if (c=='_' or c=='-' or c=='/') c=' ';
        if (c>='a' and c<='z') c=c-32;
        if (seMuestra==true) salida << c;
        cantCaracteres++;
    }
    if (seMuestra==true) salida << setw(anchoColumna-cantCaracteres) << " ";
}

void imprimirEncabezadoSedes(ifstream &entrada, ofstream &salida, int numSede) {
    salida << "SEDE: " << numSede << " - ";
    leerImprimirNombres(entrada, salida, 100, true);
    salida << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << "ATENCIONES" << endl;
    salida << left << setw(ANCHO_REPORTE/6) << "FECHA" << setw(ANCHO_REPORTE/6) << "PACIENTE"
            << setw(ANCHO_REPORTE/6) << "DURACION" << setw(ANCHO_REPORTE/6) << "MEDICO"
            << setw(ANCHO_REPORTE/6) << "ESPECIALIDAD" << setw(ANCHO_REPORTE/6) << "PAGO" << endl;
}

void buscarInfoAtenciones(ifstream &atenciones, ifstream &pacientes, ifstream &medicos, ofstream &salida, int numSede,
    int &cantAtencionesPorSede, int &tiempoTotalAtencionesPorSedeSec, double &pagoTotalPorSede) {
    int dia, mes, anio, horaI, minI, segI, horaF, minF, segF, n1, n2, n3, codigoDoctor, sedeDeAtenciones;
    char c;
    double pago;
    atenciones.clear();
    atenciones.seekg(0);

    while (atenciones >> dia >> c >> mes >> c >> anio) {
        while (atenciones.peek()!='\n') {
            if (atenciones >> sedeDeAtenciones) {
                atenciones >> horaI >> c >> minI >> c >> segI >> n1 >> c >> n2 >> c >> n3 >> horaF >> c >> minF >> c >> segF >> codigoDoctor;
                if (sedeDeAtenciones==numSede) {
                    cantAtencionesPorSede++;
                    salida << right << setw(2) << setfill('0') << cantAtencionesPorSede << ") " << setw(2) << dia
                            << "/" << setw(2) << mes << "/" << setw(4) << anio << setfill(' ') << setw(5) << " "
                            << setw(3) << setfill('0') << n1 << setw(2) << n2 << setw(3) << n3 << setfill(' ') << " - ";
                    buscarPacientes(pacientes, salida, n1, n2, n3); //BUSCAMOS EN OTRO ARCHIVO DE DATOS

                    int tiempoInicioSec=(horaI*3600)+(minI*60)+segI, tiempoFinSec=(horaF*3600)+(minF*60)+segF;
                    if (tiempoFinSec<tiempoInicioSec) tiempoFinSec=tiempoFinSec+(24*3600);
                    int duracionSec=tiempoFinSec-tiempoInicioSec;
                    tiempoTotalAtencionesPorSedeSec+=duracionSec;
                    imprimirTiempo(salida, duracionSec, 13);

                    buscarMedicos(medicos, salida, codigoDoctor, duracionSec, pago); //BUSCAMOS EN OTRO ARCHIVO DE DATOS
                    pagoTotalPorSede+=pago;
                }
            }
            else {
                atenciones.clear();
                break;
            }
        }
    }
}

double calcularPago(double costoPor1Hora, int tiempoSec) {
    return (tiempoSec*costoPor1Hora)/3600;
}

void buscarPacientes(ifstream &pacientes, ofstream &salida, int n1, int n2, int n3) {
    int a1, a2, a3, edad;
    char sep, sexo;
    pacientes.clear();
    pacientes.seekg(0);

    while (pacientes.peek()!='\n') {
        if (pacientes >> a1 >> sep >> a2 >> sep >> a3 >> ws) {
            if (a1==n1 and a2==n2 and a3==n3) {
                leerImprimirNombres(pacientes, salida, 25, true);
                pacientes >> sexo >> edad;
            }
            else { //si el id del paciente no se encuentra en la primera linea, se consume el salto de linea
                char c;
                while (pacientes.get(c) and c!='\n');
            }
        }
    }
}

void imprimirTiempo(ofstream &salida, int tiempo, int anchoColumna) {
    int hora=tiempo/3600, min=(tiempo%3600)/60, seg=tiempo%60;
    salida << right << setw(2) << setfill('0') << hora << ":" << setw(2) << min << ":" << setw(2) << seg
            << setfill(' ') << setw(anchoColumna-8) << " ";
}

void buscarMedicos(ifstream &medicos, ofstream &salida, int codigoDoctor, int duracionSec, double &pago) {
    int codigoEspecialidad, codigoMedico;
    double costoPor1Hora;
    medicos.clear();
    medicos.seekg(0);

    while (medicos >> codigoEspecialidad >> ws) {
        leerImprimirNombres(medicos, salida, 1, false); //se lee la profesion pero no se muestra
        while (medicos.peek()!='\n') {
            if (medicos >> codigoMedico >> ws) {
                if (codigoMedico==codigoDoctor) {
                    salida << right << setw(4) << setfill('0') << codigoMedico << setfill(' ') << " - ";
                    leerImprimirNombres(medicos, salida, 36, true);
                    medicos >> costoPor1Hora;
                    pago=calcularPago(costoPor1Hora, duracionSec);
                    salida << left << setw(ANCHO_REPORTE/6) << codigoEspecialidad << setw(ANCHO_REPORTE/6) << fixed
                            << setprecision(2) << pago << endl;
                }
                else {
                    leerImprimirNombres(medicos, salida, 36, false); //se lee pero no se imprime
                    medicos >> costoPor1Hora; //se termina de leer hasta el final.
                }
            }
        }
    }
}

void imprimirResumenPorSede(ofstream &salida, int cantAtencionesPorSede, double pagoTotalPorSede,
    int tiempoTotalAtencionesPorSedeSec) {
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << "TOTAL DE ATENCIONES: " << cantAtencionesPorSede << endl;
    salida << "TOTAL PAGO SEDE: S/. " << fixed << setprecision(2) << pagoTotalPorSede << endl;
    salida << "TIEMPO TOTAL ATENCIONES: ";
    imprimirTiempo(salida, tiempoTotalAtencionesPorSedeSec, 9);
    salida << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}

void imprimirResumenTotal(ofstream &salida, int cantSedes, double pagoTotal, int numSedeMayorPago,
    double mayorPagoPorSede) {
    salida << "RESUMEN TOTAL:" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << "CANTIDAD DE SEDES QUE ATENDIERON EN 2023-4: " << cantSedes << endl;
    salida << "PAGO TOTAL: S/. " << fixed << setprecision(2) << pagoTotal << endl;
    salida << "SEDE CON MAYOR PAGO: " << numSedeMayorPago << " - S/. " << fixed << setprecision(2) << mayorPagoPorSede << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}

void generarReporte(ifstream &atenciones, ifstream &medicos, ifstream &pacientes, ifstream &sedes, ofstream &salida) {
    imprimirEncabezado(salida);
    int cantSedes=0, numSedeMayorPago=0;
    double pagoTotal=0.0, mayorPagoPorSede=-1.0;
    int numSede;

    while (sedes >> numSede >> ws) {
        cantSedes++;
        imprimirEncabezadoSedes(sedes, salida, numSede);

        int cantAtencionesPorSede=0, tiempoTotalAtencionesPorSedeSec=0;
        double pagoTotalPorSede=0.0;
        //EN BASE AL numSede BUSCAMOS EN OTROS ARCHIVOS DE DATOS
        buscarInfoAtenciones(atenciones, pacientes, medicos, salida, numSede, cantAtencionesPorSede,
            tiempoTotalAtencionesPorSedeSec, pagoTotalPorSede);
        imprimirResumenPorSede(salida, cantAtencionesPorSede, pagoTotalPorSede, tiempoTotalAtencionesPorSedeSec);

        pagoTotal+=pagoTotalPorSede;
        if (mayorPagoPorSede<pagoTotalPorSede) mayorPagoPorSede=pagoTotalPorSede, numSedeMayorPago=numSede;
    }
    imprimirResumenTotal(salida, cantSedes, pagoTotal, numSedeMayorPago, mayorPagoPorSede);
}
