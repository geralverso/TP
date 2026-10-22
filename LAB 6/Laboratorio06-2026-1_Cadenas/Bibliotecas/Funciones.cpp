//
// Created by PC on 16/10/2026.
//

#include "Funciones.h"

//PARA LEER, CALCULAR, BUSCAR, ARMAR:

void cargarEspecMedicos(const char* nombreArchivo, int* &codigosMedicos, double* &tarifaMedicos, int &numMedicos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    int bufferCodigosMedicos[CAPACIDAD_MEDICOS];
    double bufferTarifaMedicos[CAPACIDAD_MEDICOS];
    numMedicos=0;
    int codEspecialidad, codigoMedico;
    double tarifa;
    while (entrada >> codEspecialidad >> ws) {
        entrada.ignore(1000, ' ');
        while (true) {
            entrada >> codigoMedico;
            entrada.ignore(1000, '/'); entrada.ignore(1000, '/'); entrada.ignore(1000, ' ');
            entrada >> tarifa;
            insertarOrdenadoEspecMedicos(bufferCodigosMedicos, bufferTarifaMedicos, codigoMedico, tarifa,
                numMedicos, CAPACIDAD_MEDICOS);
            if (entrada.get()=='\n') break;
        }
    }

    codigosMedicos=new int[numMedicos];
    tarifaMedicos=new double[numMedicos];
    for (int i=0;i<numMedicos;i++) {
        codigosMedicos[i]=bufferCodigosMedicos[i];
        tarifaMedicos[i]=bufferTarifaMedicos[i];
    }
}

int insertarOrdenadoEspecMedicos(int* codigosMedicos, double* tarifaMedicos, int codMedNuevo, double tarifaNueva,
    int &numMedicos, int capacidad) {
    if (numMedicos>=capacidad) return -1;
    int i=numMedicos-1;
    while (i>=0 and codigosMedicos[i]>codMedNuevo) {
        codigosMedicos[i+1]=codigosMedicos[i];
        tarifaMedicos[i+1]=tarifaMedicos[i];
        i--;
    }
    codigosMedicos[i+1]=codMedNuevo;
    tarifaMedicos[i+1]=tarifaNueva;
    numMedicos++;
    return i+1;
}

void cargarAtenciones(const char *nombreArchivo, int *&codigosPacientes, int *&codigosSedesPacientes,
    int *&duracionAtencionesPacientes, double *&pagosTotalesPacientes, int &numAtenciones, int* codigosMedicos,
    double* tarifaMedicos, int numMedicos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    int bufferCodigosPacientes[CAPACIDAD_ATENCIONES];
    int bufferCodigosSedesPacientes[CAPACIDAD_ATENCIONES];
    int bufferDuracionAtenciones[CAPACIDAD_ATENCIONES]{};
    double bufferPagosTotales[CAPACIDAD_ATENCIONES]{};
    numAtenciones=0;
    int dia, mes, anio, codSede, n1, n2, n3, codPaciente, codMedico, tiempoInicio, tiempoFinal, duracionAtencion;
    char c;
    while (entrada >> dia >> c >> mes >> c >> anio) {
        while (true) {
            entrada >> codSede;
            tiempoInicio=leerYCalcularTiempo(entrada);
            entrada >> n1 >> c >> n2 >> c >> n3;
            codPaciente=(n1*1000000)+(n2*10000)+n3;
            tiempoFinal=leerYCalcularTiempo(entrada);
            entrada >> codMedico;
            duracionAtencion=calcularDuracion(tiempoInicio, tiempoFinal);

            int posMedico=buscarBinariaMedico(codigosMedicos, codMedico, numMedicos);
            int pos=buscarPacienteYSede(bufferCodigosPacientes, bufferCodigosSedesPacientes, codPaciente, codSede, numAtenciones);
            if (pos==-1) { //si no se repiten
                bufferCodigosPacientes[numAtenciones]=codPaciente;
                bufferCodigosSedesPacientes[numAtenciones]=codSede;
                bufferDuracionAtenciones[numAtenciones]=duracionAtencion;
                if (posMedico!=-1) bufferPagosTotales[numAtenciones]=(duracionAtencion*tarifaMedicos[posMedico])/3600;
                numAtenciones++;
            }
            else {
                bufferDuracionAtenciones[pos]+=duracionAtencion;
                if (posMedico!=-1) bufferPagosTotales[pos]+=(duracionAtencion*tarifaMedicos[posMedico])/3600;
            }
            if (entrada.get()=='\n') break;
        }
    }

    codigosPacientes=new int[numAtenciones];
    codigosSedesPacientes=new int[numAtenciones];
    duracionAtencionesPacientes=new int[numAtenciones];
    pagosTotalesPacientes=new double[numAtenciones];
    for (int i=0; i<numAtenciones; i++) {
        codigosPacientes[i]=bufferCodigosPacientes[i];
        codigosSedesPacientes[i]=bufferCodigosSedesPacientes[i];
        duracionAtencionesPacientes[i]=bufferDuracionAtenciones[i];
        pagosTotalesPacientes[i]=bufferPagosTotales[i];
    }
}

int leerYCalcularTiempo(ifstream &entrada) {
    int hora, min, seg; char c;
    entrada >> hora >> c >> min >> c >> seg;
    return (hora*3600)+(min*60)+seg;
}

int buscarBinariaMedico(int* codigosMedicos, int codigoBuscado, int numMedicos){
    int posInicial=0, posFinal=numMedicos-1;
    while (true) {
        int posMedio=(posInicial+posFinal)/2;
        if (codigosMedicos[posMedio]==codigoBuscado) return posMedio;
        if (codigosMedicos[posMedio]<codigoBuscado) posInicial=posMedio+1;
        else posFinal=posMedio-1;
        if (posInicial>posFinal) return -1;
    }
}

int buscarPacienteYSede(int *bufferCodigosPacientes, int *bufferCodigosSedesPacientes, int codPacienteBuscado,
    int codSedeBuscado, int numAtenciones) {
    for (int i=0; i<numAtenciones; i++) {
        if (bufferCodigosPacientes[i]==codPacienteBuscado and bufferCodigosSedesPacientes[i]==codSedeBuscado) return i;
    }
    return -1;
}

void armarCadena(ifstream& entrada, char *cadena, char delimitador) {
    bool fin=false; char palabra[60];
    while (!fin) { //mientras no sea el fin de la cadena
        entrada >> palabra;
        int longitud=strlen(palabra);
        if (palabra[longitud-1]==delimitador) {
            palabra[longitud-1]='\0'; //lo marcamos como el fin de la cadena
            fin=true;
        }
        for (int i=1; palabra[i]!='\0'; i++) { //para pasar las letras (excepto la inicial) a minusculas
            if ('A'<=palabra[i] and 'Z'>=palabra[i]) palabra[i]+=32;
        }
        strcat(cadena, palabra);
        strcat(cadena, " ");
    }
}

void armarTodasLasCadenas(ifstream &entrada, char *nombreRed, char *nombreClinica, char *nombreDireccion,
    char *nombreDistrito) {

    //INICIALIZAMOS LAS CADENAS VACIAS:
    strcpy(nombreRed, "");
    strcpy(nombreClinica, "");
    strcpy(nombreDireccion, "");
    strcpy(nombreDistrito, "");

    //LEEMOS EL NOMBRE DE LA RED (termina con '!'):
    armarCadena(entrada, nombreRed, '!');

    //LEEMOS EL NOMBRE DE LA CLINICA (termina con '-'):
    armarCadena(entrada, nombreClinica, '-');

    //LEEMOS EL NOMBRE DE LA DIRECCION (termina con '}'):
    armarCadena(entrada, nombreDireccion, '}');

    //LEEMOS EL NOMBRE DE LA DISTRITO (termina con '*'):
    armarCadena(entrada, nombreDistrito, '*');
}

int buscarSede(int *codigosSedesPacientes, int codigoBuscado, int numAtenciones) {
    for (int i=0; i<numAtenciones; i++) {
        if (codigosSedesPacientes[i]==codigoBuscado) return i;
    }
    return -1;
}

int calcularDuracion(int inicio, int fin) {
    if (fin<inicio) fin+=(24*3600);
    return fin-inicio;
}


//PARA ORDENAR:

void intercambiarInt(int &a, int &b) {
    int aux=a;
    a=b, b=aux;
}

void intercambiarDouble(double &a, double &b) {
    double aux=a;
    a=b, b=aux;
}

void ordenarSedeYPacientePorBurbuja(int *codigosPacientes, int *codigosSedesPacientes, int *duracionAtencionesPacientes,
    double *pagosTotalesPacientes, int numAtenciones) {
    for (int i=0; i<(numAtenciones-1); i++) {
        for (int j=0; j<numAtenciones-1-i; j++) {
            if (codigosSedesPacientes[j]>codigosSedesPacientes[j+1] or
                (codigosSedesPacientes[j]==codigosSedesPacientes[j+1] and codigosPacientes[j]>codigosPacientes[j+1])) {
                intercambiarInt(codigosPacientes[j],codigosPacientes[j+1]);
                intercambiarInt(codigosSedesPacientes[j],codigosSedesPacientes[j+1]);
                intercambiarInt(duracionAtencionesPacientes[j],duracionAtencionesPacientes[j+1]);
                intercambiarDouble(pagosTotalesPacientes[j],pagosTotalesPacientes[j+1]);
            }
        }
    }
}


//PARA IMPRIMIR:

void imprimirSeparador(ofstream& salida, char c, int n) {
    for (int i=0;i<n;i++) salida << c;
    salida << endl;
}

void imprimirTiempoOCodigo(char tipo, int num, ofstream &salida, int ancho) {
    char cadenaTiempo[9], cadenaCodPaciente[12];
    if (tipo=='T') {
        int hora=num/3600, min=(num%3600)/60, seg=num%60;
        cadenaTiempo[0]='0'+(hora/10);
        cadenaTiempo[1]='0'+(hora%10);
        cadenaTiempo[2]=':';
        cadenaTiempo[3]='0'+(min/10);
        cadenaTiempo[4]='0'+(min%10);
        cadenaTiempo[5]=':';
        cadenaTiempo[6]='0'+(seg/10);
        cadenaTiempo[7]='0'+(seg%10);
        cadenaTiempo[8]='\0';
        salida << right << setw(ancho) << cadenaTiempo;
    }
    else {
        int n1=num/1000000, n2=(num%1000000)/10000, n3=num%10000;
        cadenaCodPaciente[0]='0'+(n1/100);
        cadenaCodPaciente[1]='0'+((n1%100)/10);
        cadenaCodPaciente[2]='0'+(n1%10);
        cadenaCodPaciente[3]='-';
        cadenaCodPaciente[4]='0'+(n2/10);
        cadenaCodPaciente[5]='0'+(n2%10);
        cadenaCodPaciente[6]='-';
        cadenaCodPaciente[7]='0'+(n3/1000);
        cadenaCodPaciente[8]='0'+((n3%1000)/100);
        cadenaCodPaciente[9]='0'+(((n3%1000)%100)/10);
        cadenaCodPaciente[10]='0'+(n3%10);
        cadenaCodPaciente[11]='\0';
        salida << left << setw(ancho) << cadenaCodPaciente;
    }
}

void imprimirDatosSede(ifstream &entrada, ofstream &salida, char *nombreRed, char *nombreClinica, char *nombreDireccion,
    char *nombreDistrito, int codigoSede) {
    armarTodasLasCadenas(entrada, nombreRed, nombreClinica, nombreDireccion, nombreDistrito);
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << "SEDE:" << endl;
    salida << left << setw(10) << "CODIGO" << setw(22) << "DISTRITO" << setw(33) << "CLINICA"
            << setw(39) << "DIRECCION" << "RED" << endl;
    salida << left << setw(10) << codigoSede << setw(22) << nombreDistrito << setw(33) << nombreClinica
            << setw(39) << nombreDireccion << nombreRed << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
}

void imprimirPacientesPorSede(ofstream &salida, int numAtenciones, int codigoSede, int *codigosSedesPacientes,
    int *codigosPacientes, int* duracionAtencionesPacientes, double* pagosTotalesPacientes, double &ingresoTotalPorSede) {
    int cantAtencionesPorSede=0;
    for (int i=0; i<numAtenciones;i++) {
        if (codigosSedesPacientes[i]==codigoSede) {
            cantAtencionesPorSede++, ingresoTotalPorSede+=pagosTotalesPacientes[i];
            salida << right << setw(2) << setfill('0') << cantAtencionesPorSede << setfill(' ') << left
                    << setw(2) << ")";
            imprimirTiempoOCodigo('C', codigosPacientes[i], salida, 15);
            imprimirTiempoOCodigo('T', duracionAtencionesPacientes[i], salida, 15);
            salida << right << setw(22) << fixed << setprecision(2) << pagosTotalesPacientes[i] << endl;
        }
    }
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
}

void imprimirResumen(ofstream &salida, char *redMayorIngreso, char *clinicaMayorIngreso, char *direccionMayorIngreso,
    char *distritoMayorIngreso, double mayorIngresoTotal) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << "SEDE CON MAYORES INGRESOS:" << endl;
    salida << left << setw(20) << "RED:" << redMayorIngreso << endl;
    salida << left << setw(20) << "CLINICA:" << clinicaMayorIngreso << endl;
    salida << left << setw(20) << "DIRECCION:" << direccionMayorIngreso << endl;
    salida << left << setw(20) << "DISTRITO:" << distritoMayorIngreso << endl;
    salida << left << setw(20) << "TOTAL DE INGRESOS:" << mayorIngresoTotal << endl;
}


//PARA GENERAR REPORTES:

void generarReporteSimple1(const char* nombreArchivo, int* codigosMedicos, double* tarifaMedicos, int numMedicos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    salida << "VERIFICACION DE MEDICOS (ORDENADO ASCENDENTEMENTE POR SU CODIGO)" << endl;
    salida << right << setw(14) << "CODIGO" << setw(14) << "TARIFA" << endl;
    for (int i=0;i<numMedicos;i++) {
        salida << right << setw(14) << codigosMedicos[i] << setw(14) << fixed << setprecision(2) << tarifaMedicos[i] << endl;
    }
}

void generarReporteSimple2(const char *nombreArchivo, int *codigosPacientes, int *codigosSedesPacientes,
    int *duracionAtencionesPacientes, double *pagosTotalesPacientes, int numAtenciones) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    salida << "VERIFICACION DE ATENCIONES (ORDENADO ASCENDENTEMENTE POR SEDE Y PACIENTE)" << endl;
    salida << right << setw(17) << "CODIGO PACIENTE" << setw(17) << "CODIGO SEDE" << setw(17) << "DUR. ATENCION"
            << setw(17) << "PAGO TOTAL" << endl;
    for (int i=0;i<numAtenciones;i++) {
        salida << right << setw(14) << codigosPacientes[i] << setw(17) << codigosSedesPacientes[i];
        imprimirTiempoOCodigo('T', duracionAtencionesPacientes[i], salida, 18);
        salida << setw(17) << fixed << setprecision(2) << pagosTotalesPacientes[i] << endl;
    }
}

void generarReporte(const char* nombreArchivo1, const char* nombreArchivo2, int *codigosMedicos, int *codigosPacientes,
    int *codigosSedesPacientes, int *duracionAtencionesPacientes, double *pagosTotalesPacientes, int numAtenciones) {
    ofstream salida(nombreArchivo1); ifstream entrada(nombreArchivo2);
    if (!salida or !entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    salida << setw((ANCHO_REPORTE+29)/2) << "CLINICA DE URGENCIAS TP_SALUD" << endl;
    salida << setw((ANCHO_REPORTE+19)/2) << "ATENCIONES POR SEDE" << endl;
    int codigoSede;
    double mayorIngresoTotal=-1.0;
    char nombreRed[100], nombreClinica[100], nombreDireccion[100], nombreDistrito[100];
    char redMayorIngreso[100]="", clinicaMayorIngreso[100]="", direccionMayorIngreso[100]="", distritoMayorIngreso[100]="";

    while (entrada >> codigoSede) {
        imprimirDatosSede(entrada, salida, nombreRed, nombreClinica, nombreDireccion, nombreDistrito, codigoSede);
        salida << "PACIENTES ATENDIDOS EN LA SEDE" << endl;
        salida << left << setw(4) << "No." << setw(15) << "CODIGO" << setw(28) << "DURACION DE ATENCIONES"
                << setw(15) << "PAGO TOTAL" << endl;

        double ingresoTotalPorSede=0.0;
        imprimirPacientesPorSede(salida, numAtenciones, codigoSede, codigosSedesPacientes, codigosPacientes,
            duracionAtencionesPacientes, pagosTotalesPacientes, ingresoTotalPorSede);
        salida << "INGRESOS TOTALES POR ATENCION: " << fixed << setprecision(2) << ingresoTotalPorSede << endl;

        if (mayorIngresoTotal<ingresoTotalPorSede) {
            mayorIngresoTotal=ingresoTotalPorSede;
            strcpy(redMayorIngreso, nombreRed);
            strcpy(clinicaMayorIngreso, nombreClinica);
            strcpy(direccionMayorIngreso, nombreDireccion);
            strcpy(distritoMayorIngreso, nombreDistrito);
        }
    }
    imprimirResumen(salida, redMayorIngreso, clinicaMayorIngreso, direccionMayorIngreso, distritoMayorIngreso, mayorIngresoTotal);
}
