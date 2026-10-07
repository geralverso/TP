//
// Created by PC on 6/10/2026.
//

#include "FuncionesAuxiliares.h"

void cargarClientesTXT(const char *nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes, int &numClientes) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numClientes=0;
    int codigo;
    char tipoDeCredito, nombre[30];
    double montoDesembolsado;
    while (entrada >> codigo >> nombre >> tipoDeCredito >> montoDesembolsado) {
        int pos=buscarCliente(codigosClientes, codigo, numClientes);
        if (pos==-1) { //SI NO HAY CODIGO REPETIDO
            codigosClientes[numClientes]=codigo;
            tiposDeCreditosClientes[numClientes]=tipoDeCredito;
            montosDesembolsadosClientes[numClientes]=montoDesembolsado;
            numClientes++;
        }
    }
}

int buscarCliente(int *codigosClientes, int codigoBuscado, int numClientes) {
    for (int i=0; i<numClientes; i++) {
        if (codigosClientes[i]==codigoBuscado) {
            return i; //SI REGRESA UNA POSICION, HAY CODIGO REPETIDO
        }
    }
    return -1; //SI REGRESA -1, NO HAY CODIGO REPETIDO
}

void cargarMovimientosTXT(const char *nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes,  int &numClientes) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    int codigo;
    char letra, tipoDeCredito, nombre[30];
    double montoDesembolsado;
    while (entrada >> letra >> codigo) {
        //HALLAMOS LA POSICION
        int posicion=buscarCliente(codigosClientes, codigo, numClientes);
        if (letra=='A') { //PARA AGREGAR
            entrada >> nombre >> tipoDeCredito >> montoDesembolsado;
            if (posicion==-1) { //SI NO SE ENCONTRÓ UN CODIGO REPETIDO
                insertarOrdenado(codigosClientes, tiposDeCreditosClientes, montosDesembolsadosClientes, codigo,
                    tipoDeCredito, montoDesembolsado,numClientes,CAPACIDAD_CLIENTES);
            }
        }
        else if (letra=='E') { //PARA ELIMINAR
            if (posicion!=-1) { //SI SE ENCUENTRA EL CODIGO
                eliminarDatos(codigosClientes, tiposDeCreditosClientes, montosDesembolsadosClientes, numClientes, posicion);
            }
        }
    }
}

bool eliminarDatos(int *codigosClientes, char *tiposDeCreditosClientes, double *montosDesembolsadosClientes,
    int &numClientes, int posicion) {
    if (posicion<0 or posicion>=numClientes) return false;
    for (int i=posicion; i<(numClientes-1); i++) {
        codigosClientes[i]=codigosClientes[i+1];
        tiposDeCreditosClientes[i]=tiposDeCreditosClientes[i+1];
        montosDesembolsadosClientes[i]=montosDesembolsadosClientes[i+1];
    }
    numClientes--;
    return true;
}

int insertarOrdenado(int *codigosClientes, char *tiposDeCreditosClientes, double *montosDesembolsadosClientes,
    int codigoNuevo, char tipoCreditoCodNuevo, double montoDesembCodNuevo, int &numClientes, int capacidad) {

    if (numClientes>=capacidad) return -1;

    int i=numClientes-1;
    while (i>=0 and codigosClientes[i]>codigoNuevo) {
        codigosClientes[i+1]=codigosClientes[i];
        tiposDeCreditosClientes[i+1]=tiposDeCreditosClientes[i];
        montosDesembolsadosClientes[i+1]=montosDesembolsadosClientes[i];
        i--;
    }
    codigosClientes[i+1]=codigoNuevo;
    tiposDeCreditosClientes[i+1]=tipoCreditoCodNuevo;
    montosDesembolsadosClientes[i+1]=montoDesembCodNuevo;
    numClientes++;

    return i+1;
}

void cargarCuotasCSV(const char* nombreArchivo, int *codigosClientesCuotas, double *montosCuotas,
    double *montosPagadosCuotas, int *cantDiasDeAtrasoCuotas, int *fechasDeVencimientoCuotas, int &numCuotas) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numCuotas=0;
    double montoCuota, montoPagado;
    int codigo, cantDiasAtraso, dia, mes, anio, fechaDeVencimientoCuota;
    char c;
    while (entrada >> codigo) {
        entrada >> c >> montoCuota >> c >> montoPagado >> c >> cantDiasAtraso >> c >> dia >> c >> mes >> c >> anio;
        fechaDeVencimientoCuota=(anio*10000)+(mes*100)+dia;
        codigosClientesCuotas[numCuotas]=codigo;
        montosCuotas[numCuotas]=montoCuota;
        montosPagadosCuotas[numCuotas]=montoPagado;
        cantDiasDeAtrasoCuotas[numCuotas]=cantDiasAtraso;
        fechasDeVencimientoCuotas[numCuotas]=fechaDeVencimientoCuota;
        numCuotas++;
    }
}

int buscarMayorDiasAtraso(int *codigosClientesCuotas, int *cantDiasDeAtrasoCuotas, int codigoBuscado, int numCuotas,
    int *fechasDeVencimientoCuotas) {
    if (numCuotas==0) return -1;
    int posicionMayor=-1;
    for (int i=0; i<numCuotas; i++) {
        if (codigosClientesCuotas[i]==codigoBuscado) {
            if (posicionMayor==-1 or cantDiasDeAtrasoCuotas[i]>cantDiasDeAtrasoCuotas[posicionMayor]) {
                posicionMayor=i;
            }
            else if (cantDiasDeAtrasoCuotas[i]==cantDiasDeAtrasoCuotas[posicionMayor] and
                fechasDeVencimientoCuotas[i]<fechasDeVencimientoCuotas[posicionMayor]) {
                posicionMayor=i; //POR DESEMPATE DE CANT DIAS Y FECHAS
            }
        }
    }
    return posicionMayor;
}

void acumularDatosClasificacion(int codigo, int numCuotas, int *codigosClientesCuotas, int *cantDiasDeAtrasoCuotas,
    int &posicionMayorCantDiasAtraso, double &saldoPendienteTotal, double *montosCuotas, double *montosPagadosCuotas,
    int *fechasDeVencimientoCuotas) {
    for (int j=0; j<numCuotas; j++) {
        if (codigosClientesCuotas[j]==codigo) { //SE RECORRETODO pagos_cuotas Y SE ENCUENTRAN LOS CODIGOS

            //SE HALLA LA POS DEL MAYOR CANT DIAS DE ATRASO
            posicionMayorCantDiasAtraso=buscarMayorDiasAtraso(codigosClientesCuotas, cantDiasDeAtrasoCuotas, codigo, numCuotas,
                fechasDeVencimientoCuotas);

            //SE HALLA EL SALDO PENDIENTE TOTAL DE CADA CODIGO
            double montoCuota=montosCuotas[j], montoPagado=montosPagadosCuotas[j];
            double saldoPendiente=montoCuota-montoPagado;
            saldoPendienteTotal+=saldoPendiente;
        }
    }
}

void intercambiarInt(int &a, int &b) {
    int aux=a;
    a=b, b=aux;
}

void intercambiarDouble(double &a, double &b) {
    double aux=a;
    a=b, b=aux;
}

void intercambiarChar(char &a, char &b) {
    char aux=a;
    a=b, b=aux;
}

void imprimirTotalClientes(ofstream &salida, int numClientes) {
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << left << setw(40) << "Total de clientes" << right << setw(20) << numClientes << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}

void ordenarPorCodigoConBurbuja(int *codigosClientes, char *tiposDeCreditosClientes, double *montosDesembolsadosClientes,
    int numClientes) {
    for (int i=0; i<(numClientes-1); i++) {
        for (int j=0; j<numClientes-1-i; j++) {
            if (codigosClientes[j]>codigosClientes[j+1]) {
                intercambiarInt(codigosClientes[j],codigosClientes[j+1]);
                intercambiarDouble(montosDesembolsadosClientes[j],montosDesembolsadosClientes[j+1]);
                intercambiarChar(tiposDeCreditosClientes[j],tiposDeCreditosClientes[j+1]);
            }
        }
    }
}

void ordenarPorDiasAtrasoConSeleccion(int *cantDiasDeAtrasoCuotas, int *codigosClientes, char *tiposDeCreditosClientes,
    int *fechasDeVencimientoCuotas, int numClientes, int *codigosClientesCuotas, int numCuotas) {

    for (int i = 0; i < (numClientes - 1); i++) {
        int posicionMayor = i;

        // 1. Obtenemos la cuota con mayor atraso para el cliente actual 'i'
        int posCuotaI = buscarMayorDiasAtraso(codigosClientesCuotas, cantDiasDeAtrasoCuotas,codigosClientes[i],
            numCuotas, fechasDeVencimientoCuotas);
        int cantDiasAtrasoMayorI;
        if (posCuotaI!=-1) cantDiasAtrasoMayorI=cantDiasDeAtrasoCuotas[posCuotaI];
        else cantDiasAtrasoMayorI=-1;

        // 2. Buscamos entre los clientes restantes si alguno tiene un atraso mayor
        for (int j = i + 1; j < numClientes; j++) {
            // Buscamos la posición de la cuota con mayor atraso del cliente j
            int posCuotaJ = buscarMayorDiasAtraso(codigosClientesCuotas, cantDiasDeAtrasoCuotas,codigosClientes[j],
                numCuotas, fechasDeVencimientoCuotas);
            int cantDiasAtrasoMayorJ;
            if (posCuotaJ!=-1) cantDiasAtrasoMayorJ=cantDiasDeAtrasoCuotas[posCuotaJ];
            else cantDiasAtrasoMayorJ=-1;

            // Comparamos días de atraso de mayor a menor (descendente)
            if (cantDiasAtrasoMayorJ > cantDiasAtrasoMayorI) {
                cantDiasAtrasoMayorI = cantDiasAtrasoMayorJ;
                posicionMayor = j;
            }
        }

        // 3. Si encontramos un cliente con mayor atraso, los intercambiamos en el padrón
        if (posicionMayor != i) {
            intercambiarInt(codigosClientes[i],codigosClientes[posicionMayor]);
            intercambiarChar(tiposDeCreditosClientes[i],tiposDeCreditosClientes[posicionMayor]);
        }
    }
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void imprimirEncabezado1y2(ofstream &salida, const char *titulo) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << right << setw(13) << "" << left << titulo << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << left << setw(14) << "CODIGO" << setw(20) << "TIPO DE CREDITO" << right << setw(24)
                << "MONTO DESEMBOLSADO" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
}

void imprimirEncabezado3(ofstream &salida) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << right << setw((ANCHO_REPORTE+39)/2) << "CLASIFICACION DE LA CARTERA DE CREDITOS" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << left << setw(4) << "No." << setw(13) << "CLASIFICACION" << right << setw(16) << "SALDO PENDIENTE"
            << setw(8) << "CODIGO" << right << setw(17) << "TIPO DE CREDITO" << right << setw(7) << "ATRASO"
            << setw(13) << "VENCIMIENTO" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}

void imprimirFecha(ofstream &salida, int fecha) {
    int anio=fecha/10000, mes=(fecha%10000)/100, dia=fecha%100;
    salida << setw(3) << " " << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/"
            << setw(4) << anio << setfill(' ') << endl;
}

void emitirReporteClientes(const char *nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes, int numClientes) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    imprimirEncabezado1y2(salida, "CLIENTES LEIDOS DEL ARCHIVO");
    for (int i=0; i<numClientes; i++) {
        int codigo=codigosClientes[i];
        char tipoDeCredito=tiposDeCreditosClientes[i];
        double montoDesembolsado=montosDesembolsadosClientes[i];
        salida << left << setw(14) << codigo;
        if (tipoDeCredito=='H') salida << setw(20) << "Hipotecario";
        if (tipoDeCredito=='C') salida << setw(20) << "Consumo";
        if (tipoDeCredito=='M') salida << setw(20) << "Microempresa";
        if (tipoDeCredito=='T') salida << setw(20) << "Tarjeta";
        salida << right << setw(24) << fixed << setprecision(2) << montoDesembolsado << endl;
    }
    imprimirTotalClientes(salida, numClientes);
}

void emitirReporteClientesMov(const char *nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes, int numClientes) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    imprimirEncabezado1y2(salida, "CLIENTES LUEGO DE LOS MOVIMIENTOS");
    for (int i=0; i<numClientes; i++) {
        int codigo=codigosClientes[i];
        char tipoDeCredito=tiposDeCreditosClientes[i];
        double montoDesembolsado=montosDesembolsadosClientes[i];
        salida << left << setw(14) << codigo;
        if (tipoDeCredito=='H') salida << setw(20) << "Hipotecario";
        if (tipoDeCredito=='C') salida << setw(20) << "Consumo";
        if (tipoDeCredito=='M') salida << setw(20) << "Microempresa";
        if (tipoDeCredito=='T') salida << setw(20) << "Tarjeta";
        salida << right << setw(24) << fixed << setprecision(2) << montoDesembolsado << endl;
    }
    imprimirTotalClientes(salida, numClientes);
}

void emitirReporteClasificacionCartera(const char* nombreArchivo, int *codigosClientesCuotas, double *montosCuotas,
    double *montosPagadosCuotas, int *cantDiasDeAtrasoCuotas, int *fechasDeVencimientoCuotas, char *tiposDeCreditosClientes,
    int *codigosClientes, int numCuotas, int numClientes) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    int cantClientesConCuotas=0;
    imprimirEncabezado3(salida);
    for (int i=0; i<numClientes; i++) {
        int codigo=codigosClientes[i];
        char tipoDeCredito=tiposDeCreditosClientes[i];

        int posicionMayorCantDiasAtraso=-1; double saldoPendienteTotal=0.0;
        acumularDatosClasificacion(codigo, numCuotas, codigosClientesCuotas, cantDiasDeAtrasoCuotas,posicionMayorCantDiasAtraso,
            saldoPendienteTotal, montosCuotas, montosPagadosCuotas, fechasDeVencimientoCuotas);

        int posicionClienteCuota=buscarCliente(codigosClientesCuotas, codigo, numCuotas);
        if (posicionClienteCuota>=0) { //SI SE ENCUENTRA EL CODIGO
            cantClientesConCuotas++;
            salida << left << setw(4) << cantClientesConCuotas << right;
            if (posicionMayorCantDiasAtraso!=-1) {
                int cantDiasAtraso=cantDiasDeAtrasoCuotas[posicionMayorCantDiasAtraso];
                if (cantDiasAtraso<=8) salida << setw(13) << "Normal";
                if (cantDiasAtraso>=9 and cantDiasAtraso<=60) salida << setw(13) << "Deficiente";
                if (cantDiasAtraso>60) salida << setw(13) << "Perdida";
                salida << right << setw(16) << fixed << setprecision(2) << saldoPendienteTotal << setw(8) << codigo;
                if (tipoDeCredito=='H') salida << setw(17) << "Hipoteca";
                if (tipoDeCredito=='C') salida << setw(17) << "Consumo";
                if (tipoDeCredito=='M') salida << setw(17) << "Microempresa";
                if (tipoDeCredito=='T') salida << setw(17) << "Tarjeta";
                salida << right << setw(7) << cantDiasAtraso;
                imprimirFecha(salida, fechasDeVencimientoCuotas[posicionMayorCantDiasAtraso]);
            }
        }
    }
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}
