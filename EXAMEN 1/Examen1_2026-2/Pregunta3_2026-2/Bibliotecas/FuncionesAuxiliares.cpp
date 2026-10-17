//
// Created by PC on 16/10/2026.
//

#include "FuncionesAuxiliares.h"


void cargarProductos(const char* nombre, int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int &numProductos) {
    ifstream entrada(nombre);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numProductos=0;
    int codigoProd, stockInicial;
    char cat, c;
    double precioUnit;
    while (entrada >> codigoProd >> c) {
        entrada >> cat >> c >> stockInicial >> c >> precioUnit;
        entrada.ignore(1000, '\n');
        insertarOrdenadoProductos(codigosProductos, categoriasProductos, stocksInicialesProductos, preciosUnitProductos,
            numProductos, codigoProd, cat, stockInicial, precioUnit, CAPACIDAD_PRODUCTOS);
    }
}

int insertarOrdenadoProductos(int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int &numProductos, int codigoProdNuevo, char catProdNuevo, int stockInProdNuevo,
    double precioUnitProdNuevo, int capacidad) {
    if (numProductos>=capacidad) return -1;
    int i=numProductos-1;
    while (i>=0 and codigosProductos[i]>codigoProdNuevo) {
        codigosProductos[i+1]=codigosProductos[i];
        categoriasProductos[i+1]=categoriasProductos[i];
        stocksInicialesProductos[i+1]=stocksInicialesProductos[i];
        preciosUnitProductos[i+1]=preciosUnitProductos[i];
        i--;
    }
    codigosProductos[i+1]=codigoProdNuevo;
    categoriasProductos[i+1]=catProdNuevo;
    stocksInicialesProductos[i+1]=stockInProdNuevo;
    preciosUnitProductos[i+1]=precioUnitProdNuevo;
    numProductos++;
    return i+1;
}

int buscarBinariaProducto(int *codigosProductos, int codigoBuscado, int numProductos) {
    int posInicial=0, posFinal=numProductos-1;
    while (true) {
        int posMedio=(posInicial+posFinal)/2;
        if (codigosProductos[posMedio]==codigoBuscado) return posMedio;
        if (codigosProductos[posMedio]<codigoBuscado) posInicial=posMedio+1;
        else posFinal=posMedio-1;
        if (posInicial>posFinal) return -1;
    }
}

void leerMovimientos(const char *nombre, int *codigosProductos, int *totalIngresosProductos, int *totalEgresosProductos,
    int numProductos) {
    ifstream entrada(nombre);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    int dia, mes, anio, codigoProd, cantProductosMov;
    char c, tipoDeMovimiento;
    while (entrada >> dia >> c >> mes >> c >> anio) {
        while (entrada.peek()!='\n') {
            entrada >> codigoProd >> tipoDeMovimiento >> cantProductosMov;
            int pos=buscarBinariaProducto(codigosProductos, codigoProd, numProductos);
            if (pos!=-1) {
                if (tipoDeMovimiento=='I') totalIngresosProductos[pos]+=cantProductosMov;
                else totalEgresosProductos[pos]+=cantProductosMov;
            }
        }
    }
}

void armarArregloStocksFinales(int *stocksFinalesProductos, int *stocksInicialesProductos, int *totalIngresosProductos,
    int *totalEgresosProductos, int numProductos) {
    for (int i=0; i<numProductos; i++) {
        stocksFinalesProductos[i]=stocksInicialesProductos[i]+totalIngresosProductos[i]-totalEgresosProductos[i];
    }
}

void armarArregloMontoTotal(double *montosTotalesProductos, int *stocksFinalesProductos, double *preciosUnitProductos,
    int numProductos) {
    for (int i=0; i<numProductos; i++) montosTotalesProductos[i]=stocksFinalesProductos[i]*preciosUnitProductos[i];
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

void ordenarCategoriasYStockFinalConBubble(int numProductos, int *codigosProductos, char *categoriasProductos,
    int *stocksInicialesProductos, double *preciosUnitProductos, int *totalIngresosProductos,
    int *totalEgresosProductos, int *stocksFinalesProductos, double *montosTotalesProductos) {
    for (int i=0; i<(numProductos-1); i++) {
        for (int j=0; j<(numProductos-1-i); j++) {
            if (categoriasProductos[j]>categoriasProductos[j+1] or
                (categoriasProductos[j]==categoriasProductos[j+1] and stocksFinalesProductos[j]<stocksFinalesProductos[j+1])) {
                intercambiarChar(categoriasProductos[j],categoriasProductos[j+1]);
                intercambiarInt(codigosProductos[j],codigosProductos[j+1]);
                intercambiarInt(stocksInicialesProductos[j],stocksInicialesProductos[j+1]);
                intercambiarInt(totalIngresosProductos[j],totalIngresosProductos[j+1]);
                intercambiarInt(totalEgresosProductos[j],totalEgresosProductos[j+1]);
                intercambiarInt(stocksFinalesProductos[j],stocksFinalesProductos[j+1]);
                intercambiarDouble(preciosUnitProductos[j],preciosUnitProductos[j+1]);
                intercambiarDouble(montosTotalesProductos[j],montosTotalesProductos[j+1]);
            }
        }
    }
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void imprimirEncabezado(ofstream &salida) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << right << setw(70) << "KARDEX DE PRODUCTOS" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << "CATEGORIA" << right << setw(10) << "CODIGO" << setw(18) << "STOCK INICIAL"
            << setw(18) << "TOTAL INGRESOS" << setw(18) << "TOTAL EGRESOS" << setw(18) << "STOCK FINAL"
            << setw(10) << "PRECIO" << setw(18) << "MONTO TOTAL" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
}

void generarReporteSimple(const char *nombre, int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int numProductos) {
    ofstream salida(nombre);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    salida << "LISTADO DE PRODUCTOS ORDENADOS ASCENDENTEMENTE POR CÓDIGO" << endl;
    salida << right << setw(9) << "CODIGO" << setw(11) << "CATEGORIA" << setw(15) << "STOCK INICIAL"
            << setw(10) << "PRECIO" << endl;
    for (int i = 0; i < numProductos; i++) {
        int codigoProd=codigosProductos[i];
        char categoria=categoriasProductos[i];
        int stockInicial=stocksInicialesProductos[i];
        double precioUnit=preciosUnitProductos[i];
        salida << right << setw(8) << codigoProd << setw(8) << categoria << setw(13) << stockInicial
            << setw(16) << fixed << setprecision(2) << precioUnit << endl;
    }
}

void generarListado(const char *nombre, int *stocksFinalesProductos, int *codigosProductos, char *categoriasProductos,
    int numProductos) {
    ofstream salida(nombre);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    for (int i=0; i<numProductos; i++) {
        if (stocksFinalesProductos[i]==0) salida << categoriasProductos[i] << "," << codigosProductos[i] << endl;
    }
}

void generarReporte(const char *nombre, int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int *totalIngresosProductos, int *totalEgresosProductos, int *stocksFinalesProductos,
    double *montosTotalesProductos, int numProductos) {
    ofstream salida(nombre);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    imprimirEncabezado(salida);
    for (int i=0; i<numProductos; i++) {
        char categoria=categoriasProductos[i];
        int codigoProd=codigosProductos[i];
        int stockInicial=stocksInicialesProductos[i];
        int totalIngreso=totalIngresosProductos[i];
        int totalEgreso=totalEgresosProductos[i];
        int stockFinal=stocksFinalesProductos[i];
        double precioUnit=preciosUnitProductos[i];
        double montoTotal=montosTotalesProductos[i];

        if (stockFinal>0) {
            salida << right << setw(5) << categoria << setw(13) << codigoProd << setw(13) << stockInicial
                << setw(17) << totalIngreso << setw(19) << totalEgreso << setw(21) << stockFinal << setw(14)
                << fixed << setprecision(2) << precioUnit << setw(17) << montoTotal << endl;
        }
    }
}