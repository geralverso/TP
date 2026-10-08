//
// Created by PC on 8/10/2026.
//

#include "FuncionesAuxiliares.h"

void cargarAtenciones(const char *nombreArchivo, int *codigosMedicos, int *cantAtencionesMedicos,
    int *tiempoTotalAtencionesMedicos, int &numMedicos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    numMedicos=0;
    int codigoMedico, dia, mes, anio, numSede, n1, n2, n3;
    char c;
    while (entrada >> dia >> c >> mes >> c >> anio) {

        while (entrada.peek()!='\n' and entrada.peek()!=EOF) {
            //LEEMOS:
            entrada >> numSede;
            int tiempoInicio=leerYCalcularTiempoEnSec(entrada);
            entrada >> n1 >> c >> n2 >> c >> n3;
            int tiempoFin=leerYCalcularTiempoEnSec(entrada);
            entrada >> codigoMedico;
            if (tiempoFin<tiempoInicio) tiempoFin=tiempoFin+(24*3600);
            int duracionAtencion=tiempoFin-tiempoInicio;

            int posicionMedico=buscarMedico(codigoMedico, codigosMedicos, numMedicos);
            if (posicionMedico==-1) { //SI NO SE REPITE EL CODIGO DEL MEDICO
                codigosMedicos[numMedicos]=codigoMedico;
                cantAtencionesMedicos[numMedicos]=1; //si se encuentra 1 atencion del medico x 1ra vez
                tiempoTotalAtencionesMedicos[numMedicos]=duracionAtencion; //la duracion de esa atencion se almacena
                numMedicos++;
            }
            else { //SI EL MEDICO SE REPITE ES PORQUE TIENE UNA CANTIDAD DE ATENCIONES > 1
                cantAtencionesMedicos[posicionMedico]++; //la posicion corresponde a la 1ra vez que apareció el medico
                tiempoTotalAtencionesMedicos[posicionMedico]+=duracionAtencion;
            }
            //while (entrada.peek()==' ') entrada.get();
        }
        //if (entrada.peek()=='\n') entrada.get();
    }
}

int leerYCalcularTiempoEnSec(ifstream &entrada) {
    int hora, min, seg; char c;
    entrada >> hora >> c >> min >> c >> seg;
    return (hora*3600)+(min*60)+seg;
}

int buscarMedico(int codigoBuscado, int *codigosMedicos, int numMedicos) {
    for (int i=0; i<numMedicos; i++) {
        if (codigosMedicos[i]==codigoBuscado) {
            return i;
        }
    }
    return -1;
}

void cargarEspecialidades(const char* nombreArchivo, int *codigosEspecialidades, double *tarifasMedicos,
    int &numEspecialidades, int *codigosMedicos, int numMedicos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    numEspecialidades=0;
    int codigoEspecialidad, codigoDoctor;
    char especialidad[20], doctor[40];
    double tarifa;
    while (entrada >> codigoEspecialidad >> especialidad) {
        while (entrada.peek()!='\n' and entrada.peek()!=EOF) {
            entrada >> codigoDoctor >> doctor >> tarifa;
            int posicion=buscarMedico(codigoDoctor, codigosMedicos, numMedicos);
            if (posicion!=-1) {
                tarifasMedicos[posicion]=tarifa;
                codigosEspecialidades[posicion]=codigoEspecialidad;
            }
        }
        numEspecialidades++;
    }
}

double calcularPago(double tarifa, int tiempoSec) {
    return (tiempoSec*tarifa)/3600;
}

void armarArregloPagos(double *pagosRecibidosMedicos, int numMedicos, double *tarifasMedicos,
    int *tiempoTotalAtencionesMedicos){
    for (int i=0; i<numMedicos; i++) {
        double pago=calcularPago(tarifasMedicos[i], tiempoTotalAtencionesMedicos[i]);
        pagosRecibidosMedicos[i]=pago;
    }
}

void armarArregloTiempoPromedio(int *tiempoPromAtencionesMedicos, int *tiempoTotalAtencionesMedicos, int numMedicos,
    int *cantAtencionesMedicos) {
    for (int i=0; i<numMedicos; i++) {
        double tiempoPromSec=(cantAtencionesMedicos[i]>0)?(tiempoTotalAtencionesMedicos[i]/cantAtencionesMedicos[i]):0.0;
        tiempoPromAtencionesMedicos[i]=tiempoPromSec;
    }
}

bool eliminarDatos(int *codigosMedicos, int *cantAtencionesMedicos, double *tarifasMedicos, int *codigosEspecialidades,
    int *tiempoPromAtencionesMedicos, int *tiempoTotalAtencionesMedicos, double *pagosRecibidosMedicos, int &numMedicos,
    int posicion) {
    if (posicion<0 or posicion>=numMedicos) return false;
    for (int i=posicion; i<(numMedicos-1); i++) {
        codigosMedicos[i]=codigosMedicos[i+1];
        codigosEspecialidades[i]=codigosEspecialidades[i+1];
        tarifasMedicos[i]=tarifasMedicos[i+1];
        cantAtencionesMedicos[i]=cantAtencionesMedicos[i+1];
        tiempoTotalAtencionesMedicos[i]=tiempoTotalAtencionesMedicos[i+1];
        tiempoPromAtencionesMedicos[i]=tiempoPromAtencionesMedicos[i+1];
        pagosRecibidosMedicos[i]=pagosRecibidosMedicos[i+1];
    }
    numMedicos--;
    return true;
}

void eliminarDatosDeLosArreglos(int *codigosMedicos, int *cantAtencionesMedicos, double *tarifasMedicos,
    int *codigosEspecialidades, int *tiempoPromAtencionesMedicos, int *tiempoTotalAtencionesMedicos,
    double *pagosRecibidosMedicos, int &numMedicos) {
    for (int i=0; i<numMedicos; i++) {
        if (pagosRecibidosMedicos[i]<5000) {
            eliminarDatos(codigosMedicos, cantAtencionesMedicos, tarifasMedicos, codigosEspecialidades,
                tiempoPromAtencionesMedicos, tiempoTotalAtencionesMedicos, pagosRecibidosMedicos, numMedicos, i);
            i--;
        }
    }
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void imprimirTiempo(ofstream &salida, int tiempo) {
    int hora=tiempo/3600, min=(tiempo%3600)/60, seg=tiempo%60;
    salida << right << setw(2) << setfill('0') << hora << ":" << setw(2) << min << ":" << setw(2) << seg << setfill(' ');
}

void imprimirEncabezado(ofstream &salida, int ancho, int cantCar1, int cantCar2, const char* titulo1, const char* titulo2) {
    imprimirSeparador(salida, '=', ancho);
    salida << right << setw((ancho+cantCar1)/2) << titulo1 << endl;
    salida << right << setw((ancho+cantCar2)/2) << titulo2 << endl;
    imprimirSeparador(salida, '=', ancho);
}

void imprimirCabecerasCompletas(ofstream &salida, int tipo) {
    if (tipo==1) imprimirEncabezado(salida, ANCHO_REPORTE, 29, 21, "CLINICA DE URGENCIAS TP_SALUD",
        "ATENCIONES POR MEDICO");
    else imprimirEncabezado(salida, ANCHO_REPORTE, 29, 32, "CLINICA DE URGENCIAS TP_SALUD",
        "ATENCIONES MEDICOS MEJOR PAGADOS");
    salida << left << setw(10) << "MEDICO" << setw(16) << "ESPECIALIDAD" << setw(10) << "TARIFA" << setw(19)
            << "CANT.ATENCIONES" << setw(28) << "TIEMPO.TOTAL.ATENCIONES" << setw(27) << "TIEMPO.PROM.ATENCION"
            << "PAGO_RECIBIDO" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
}

void imprimirResumen(ofstream &salida, int numMedicos, double pagoTotal) {
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << "RESUMEN:" << endl;
    salida << "TOTAL DE MEDICOS: " << numMedicos << endl;
    salida << "PAGO TOTAL RECIBIDO: S/. " << fixed << setprecision(2) << pagoTotal << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}

void generarReportePrueba(const char* nombreArchivo, int *codigosMedicos, int *cantAtencionesMedicos,
    int *tiempoTotalAtencionesMedicos, int numMedicos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    imprimirEncabezado(salida, 50, 17, 20,"REPORTE DE PRUEBA", "DATOS DE LOS MEDICOS");
    salida << left << setw(12) << "CODIGO" << setw(22) << "CANT. ATENCIONES" << setw(15) << "TIEMPO TOTAL" << endl;
    imprimirSeparador(salida, '-', 50);
    for (int i=0; i<numMedicos; i++) {
        int codigoMedico=codigosMedicos[i];
        int cantAtenciones=cantAtencionesMedicos[i];
        int tiempoTotalAtencion=tiempoTotalAtencionesMedicos[i];
        salida << left << setw(18) << codigoMedico << setw(16) << cantAtenciones;
        imprimirTiempo(salida, tiempoTotalAtencion);
        salida << endl;
    }
    imprimirSeparador(salida, '=', 50);
}

void generarReporteAtencionesMedicos(const char* nombreArchivo, int *codigosMedicos, double *tarifasMedicos,
    int *codigosEspecialidades, int *cantAtencionesMedicos, int *tiempoTotalAtencionesMedicos, int numMedicos,
    int *tiempoPromAtencionesMedicos, double *pagosRecibidosMedicos, int tipo) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    imprimirCabecerasCompletas(salida, tipo);
    double pagoTotal=0.0;
    for (int i=0; i<numMedicos; i++) {
        int codigoMedico=codigosMedicos[i];
        int codigoEspecialidad=codigosEspecialidades[i];
        double tarifa=tarifasMedicos[i];
        int cantAtenciones=cantAtencionesMedicos[i];
        int tiempoAtencionSec=tiempoTotalAtencionesMedicos[i];
        int tiempoPromSec=tiempoPromAtencionesMedicos[i];
        double pago=pagosRecibidosMedicos[i];
        pagoTotal+=pago;
        salida << " " << left << setw(13) << codigoMedico << setw(12) << codigoEspecialidad << setw(16) << fixed
                << setprecision(2) << tarifa << setw(19) << cantAtenciones;
        imprimirTiempo(salida, tiempoAtencionSec);
        salida << setw(20) << " ";
        imprimirTiempo(salida, tiempoPromSec);
        salida << setw(16) << " " << fixed << setprecision(2) << pago << endl;
    }
    imprimirResumen(salida, numMedicos, pagoTotal);
}


