//
// Created by PC on 9/10/2026.
//

#include "Funciones.h"

// ----------------------------------------------------- REPORTE 1:

bool abrirArchivos(ifstream &planes, ifstream &usuarios, ifstream &llamadas, ofstream &salida) {
    planes.open("ArchivosDeDatos/planes.txt");
    usuarios.open("ArchivosDeDatos/usuarios.csv");
    llamadas.open("ArchivosDeDatos/llamadas.txt");
    salida.open("ArchivosDeReporte/reporte_llamadas_usuarios.txt");
    return planes.is_open() && usuarios.is_open() && llamadas.is_open() && salida.is_open();
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void leerEImprimirNombres(ifstream &entrada, ofstream &salida, bool seMuestra) {
    char c;
    while (true) {
        c=entrada.get();
        if (c=='\n' or c==',') break;
        if (seMuestra==true) salida << c;
    }
}

void imprimirTiempoOFecha(int a, int b, int c, char tipo, ofstream &salida) {
    if (tipo=='F') {
        salida << right << setw(2) << setfill('0') << a << "/" << setw(2) << b << "/" << setw(4) << c << setfill(' ') << "  ";
    }
    if (tipo=='T') {
        salida << right << setw(2) << setfill('0') << a << ":" << setw(2) << b << ":" << setw(2) << c << setfill(' ');
    }
}

int calcularDuracionSec(int hora1, int min1, int seg1, int hora2, int min2, int seg2) {
    int tiempoInicio=(hora1*3600)+(min1*60)+seg1, tiempoFin=(hora2*3600)+(min2*60)+seg2;
    if (tiempoFin<tiempoInicio) tiempoFin+=(24*3600);
    return tiempoFin-tiempoInicio;
}

double leerEImprimirPlan_Y_ObtenerPrecio(ifstream &usuarios, ifstream &planes, ofstream &salida) {
    //LEEMOS E IMPRIMIMOS LAS 2 PRIMERAS LETRAS DEL NOMBRE DEL PLAN en usuarios.csv:
    char u1=usuarios.get(), u2=usuarios.get();
    salida << u1 << u2;

    //LEEMOS E IMPRIMIMOS EL RESTO DEL NOMBRE DEL PLAN:
    leerEImprimirNombres(usuarios, salida, true);

    //AHORA BUSCAMOS ESAS 2 PRIMERAS LETRAS EN planes.txt PARA OBTENER EL PRECIO:
    planes.clear();
    planes.seekg(0);
    char p1, p2, c;
    double precio;
    while (planes >> p1 >> p2) {
        if (p1==u1 and p2==u2) {
            while (planes.get(c)) if (c=='\n' or c==' ') break;
            planes >> precio;
            return precio;
        }
        //while (planes.get(c) and c!='\n') planes.get();
        while(planes.get(c)) if(c=='\n') break;
    }
    return precio;
}

void buscarLlamadas(ifstream &llamadas, ofstream &salida, int telefono, int &cantLlamadasPorNumero,
    int &tiempoDuracionSecTotal) {
    int numeroTelf, horaI, minI, segI, horaF, minF, segF, dia, mes, anio;
    char c;
    llamadas.clear();
    llamadas.seekg(0);
    while (llamadas >> numeroTelf) {
        llamadas >> horaI >> c >> minI >> c >> segI >> horaF >> c >> minF >> c >> segF >> dia >> c >> mes >> c >> anio;

        if (numeroTelf == telefono){
            cantLlamadasPorNumero++;
            imprimirTiempoOFecha(dia, mes, anio, 'F', salida);
            int duracionSec=calcularDuracionSec(horaI, minI, segI, horaF, minF, segF);
            int horaD=duracionSec/3600, minD=(duracionSec%3600)/60, segD=duracionSec%60;
            imprimirTiempoOFecha(horaD, minD, segD, 'T', salida);
            salida << endl;

            tiempoDuracionSecTotal+=duracionSec;
        }
    }
}

void imprimirResumenDeCadaUsuario(ofstream &salida, int tiempoDuracionSecTotal, int cantLlamadasPorNumero, double precio,
    double &monto) {
    int hora=tiempoDuracionSecTotal/3600, min=(tiempoDuracionSecTotal%3600)/60, seg=tiempoDuracionSecTotal%60;
    double tiempoDuracionMinTotal=(double)tiempoDuracionSecTotal/60;
    monto=tiempoDuracionMinTotal*precio;
    salida << "\nRESUMEN: " << cantLlamadasPorNumero << " llamada(s) | Tiempo total: ";
    imprimirTiempoOFecha(hora, min, seg, 'T', salida);
    salida << " (" << fixed << setprecision(2) << tiempoDuracionMinTotal << " min) | Monto a cancelar: S/ "
            << fixed << setprecision(2) << monto << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE1);
}

void imprimirResumenFinal(ofstream &salida, int cantUsuarios, int cantLlamadas, double montoTotal) {
    salida << "Total de usuarios: " << cantUsuarios << endl;
    salida << "Total de llamadas: " << cantLlamadas << endl;
    salida << "Monto total a cobrar: S/ " << fixed << setprecision(2) << montoTotal << endl;
}

void generarReporte1(ifstream &planes, ifstream &usuarios, ifstream &llamadas, ofstream &salida) {
    salida << "REPORTE DE LLAMADAS POR USUARIO" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE1);
    int dni, telefono, cantUsuarios=0, cantLlamadas=0;
    char c;
    double montoTotal=0.0;
    while (usuarios >> dni >> c) {
        cantUsuarios++;
        salida << left << setw(9) << "DNI" << ": " << dni << endl;
        salida << left << setw(9) << "Nombre" << ": ";
        leerEImprimirNombres(usuarios, salida, true);
        usuarios >> telefono >> c;
        salida << "\n" << left << setw(9) << "Telefono" << ": " << telefono << endl;
        salida << left << setw(9) << "Plan" << ": ";
        double precio=leerEImprimirPlan_Y_ObtenerPrecio(usuarios, planes, salida); // <---------
        salida << " (S/ " << fixed << setprecision(2) << precio << " por minuto) \n" << endl;

        int cantLlamadasPorNumero=0, tiempoDuracionSecTotal=0;
        double monto;
        salida << left << setw(12) << "Fecha" << "Duracion" << endl;
        buscarLlamadas(llamadas, salida, telefono, cantLlamadasPorNumero, tiempoDuracionSecTotal);

        imprimirResumenDeCadaUsuario(salida, tiempoDuracionSecTotal, cantLlamadasPorNumero, precio, monto);
        cantLlamadas+=cantLlamadasPorNumero;
        montoTotal+=monto;
    }
    imprimirResumenFinal(salida, cantUsuarios, cantLlamadas, montoTotal);
}

void cerrarArchivos(ifstream &planes, ifstream &usuarios, ifstream &llamadas, ofstream &salida) {
    planes.close();
    usuarios.close();
    llamadas.close();
    salida.close();
}


// ----------------------------------------------------- REPORTE 2:

void cargarUsuarios(const char *nombreArchivo, int *dnisUsuarios, int *telefonosUsuarios, int &numUsuarios) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numUsuarios=0;
    int dni, telefono;
    while (entrada >> dni) {
        entrada.ignore(1000, ',');
        entrada.ignore(1000, ',');
        entrada >> telefono;
        entrada.ignore(1000, '\n');
        dnisUsuarios[numUsuarios]=dni;
        telefonosUsuarios[numUsuarios]=telefono;
        numUsuarios++;
    }
}

void cargarLlamadas(const char *nombreArchivo, int *telefonosUsuarios, int numUsuarios, int *cantLlamadasUsuarios,
    int *duracionTotalLlamadas, int *fechaUltimasLlamadas, int &numLlamadas) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numLlamadas=0;
    int telefono, horaI, minI, segI, horaF, minF, segF, dia, mes, anio;
    char c;

    while (entrada >> telefono) {
        entrada >> horaI >> c >> minI >> c >> segI >> horaF >> c >> minF >> c >> segF >> dia >> c >> mes >> c >> anio;
        int duracionSec=calcularDuracionSec(horaI, minI, segI, horaF, minF, segF);
        int fecha=(anio*10000)+(mes*100)+dia;

        int posicionTel=buscarPosTelefono(telefonosUsuarios, telefono, numUsuarios);
        if (posicionTel!=-1) { //SI SE ENCUENTRA EN telefonosUsuarios CIERTAS VECES, LA CANT LLAMADAS Y DURACION AUMENTAN
            cantLlamadasUsuarios[posicionTel]++;
            duracionTotalLlamadas[posicionTel]+=duracionSec;
            if (fecha>fechaUltimasLlamadas[posicionTel]) fechaUltimasLlamadas[posicionTel]=fecha;
        }
        numLlamadas++;
    }
}

int buscarPosTelefono(int *telefonosUsuarios, int telefonoBuscado, int numUsuarios) {
    for (int i=0; i<numUsuarios; i++) {
        if (telefonosUsuarios[i] == telefonoBuscado) {
            return i;
        }
    }
    return -1;
}

void imprimirEncabezado(ofstream &salida) {
    salida << "LISTADO RESUMEN DE LLAMADAS POR USUARIO" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE2);
    salida << left << setw(10) << "DNI" << setw(12) << "Telefono" << right << setw(9) << "Llamadas" << "  "
            << left << setw(13) << "Tiempo total" << "Ultima llamada" << endl;
}

void imprimirResumen(ofstream &salida, int numLlamadas, int duracionTotalSec) {
    imprimirSeparador(salida, '-', ANCHO_REPORTE2);
    salida << "TOTAL" << right << setw(31-5) << numLlamadas << "  ";
    int hora=duracionTotalSec/3600, min=(duracionTotalSec%3600)/60, seg=duracionTotalSec%60;
    imprimirTiempoOFecha(hora, min, seg, 'T', salida);
}

void generarReporte2(const char *nombreArchivo, int *dnisUsuarios, int *telefonosUsuarios, int &numUsuarios,
    int *cantLlamadasUsuarios, int *duracionTotalLlamadas, int *fechaUltimasLlamadas, int numLlamadas) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    imprimirEncabezado(salida);
    int duracionTotalSec=0;
    for (int i=0; i<numUsuarios; i++) {
        int dni=dnisUsuarios[i];
        int telefono=telefonosUsuarios[i];
        int cantLlamadas=cantLlamadasUsuarios[i];
        int duracionSec=duracionTotalLlamadas[i];
        int fecha=fechaUltimasLlamadas[i];
        int hora=duracionSec/3600, min=(duracionSec%3600)/60, seg=duracionSec%60;
        int anio=fecha/10000, mes=(fecha%10000)/100, dia=fecha%100;
        duracionTotalSec+=duracionSec;

        salida << left << setw(10) << dni << setw(12) << telefono << right << setw(9) << cantLlamadas << "  ";
        imprimirTiempoOFecha(hora, min, seg, 'T', salida);
        salida << left << setw(13-8) << " ";
        imprimirTiempoOFecha(dia, mes, anio, 'F', salida);
        salida << endl;
    }
    imprimirResumen(salida, numLlamadas, duracionTotalSec);
}

