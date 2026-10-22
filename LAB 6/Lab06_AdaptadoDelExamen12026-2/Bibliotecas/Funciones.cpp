//
// Created by PC on 16/10/2026.
//

#include "Funciones.h"

void cargarProductos(const char *nombreArchivo, char *&categorias, int *&codigosProductos, int *&stocksIniciales,
    double *&preciosUnitarios, int &numProductos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    int bufferCodigosProductos[CAPACIDAD_PRODUCTOS];
    char bufferCategorias[CAPACIDAD_PRODUCTOS];
    int bufferStocksIniciales[CAPACIDAD_PRODUCTOS];
    double bufferPreciosUnitarios[CAPACIDAD_PRODUCTOS];

    numProductos=0;
    int codigoProd, stockInicial;
    char categoria, c;
    double precio;
    while (entrada >> codigoProd >> c) {
        entrada >> categoria >> c >> stockInicial >> c >> precio;
        entrada.ignore(1000, '\n');
        insertarOrdenadoProductos(bufferCategorias, bufferCodigosProductos, bufferStocksIniciales, bufferPreciosUnitarios,
            categoria, codigoProd, stockInicial, precio, numProductos, CAPACIDAD_PRODUCTOS);
    }

    codigosProductos= new int[numProductos];
    categorias= new char[numProductos];
    stocksIniciales= new int[numProductos];
    preciosUnitarios= new double[numProductos];

    for (int i=0;i<numProductos;i++) {
        codigosProductos[i]= bufferCodigosProductos[i];
        categorias[i]= bufferCategorias[i];
        stocksIniciales[i]= bufferStocksIniciales[i];
        preciosUnitarios[i]= bufferPreciosUnitarios[i];
    }
}

int insertarOrdenadoProductos(char *categorias, int *codigosProductos, int *stocksIniciales, double *preciosUnitarios,
    char catNuevo, int codProdNuevo, int stockInicialNuevo, double precioNuevo, int &numProductos, int capacidad) {
    if (numProductos>=capacidad) return -1;
    int i=numProductos-1;
    while (i>=0 and codigosProductos[i]>codProdNuevo) {
        codigosProductos[i+1]=codigosProductos[i];
        categorias[i+1]=categorias[i];
        stocksIniciales[i+1]=stocksIniciales[i];
        preciosUnitarios[i+1]=preciosUnitarios[i];
        i--;
    }
    codigosProductos[i+1]=codProdNuevo;
    categorias[i+1]=catNuevo;
    stocksIniciales[i+1]=stockInicialNuevo;
    preciosUnitarios[i+1]=precioNuevo;
    numProductos++;
    return i+1;
}

void cargarMovimientos(const char *nombreArchivo, int* codigosProductos, int *&totalIngresos, int *&totalEgresos,
    int numProductos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    int bufferTotalIngresos[CAPACIDAD_PRODUCTOS]{};
    int bufferTotalEgresos[CAPACIDAD_PRODUCTOS]{};

    int dia, mes, anio, cantProdMovidos, codigoProd;
    char c, tipoDeMovimiento;
    while (entrada >> dia >> c >> mes >> c >> anio) {
        while (entrada.peek()!='\n') {
            entrada >> codigoProd >> tipoDeMovimiento >> cantProdMovidos;
            int posicion=buscarBinariaProductos(codigosProductos, codigoProd, numProductos);
            if (posicion!=-1) {
                if (tipoDeMovimiento=='I') bufferTotalIngresos[posicion]+=cantProdMovidos;
                else bufferTotalEgresos[posicion]+=cantProdMovidos;
            }
        }
    }

    totalIngresos= new int[numProductos];
    totalEgresos= new int[numProductos];
    for (int i=0; i<numProductos; i++) {
        totalIngresos[i]= bufferTotalIngresos[i];
        totalEgresos[i]= bufferTotalEgresos[i];
    }
}

int buscarBinariaProductos(int *codigosProductos, int codigoBuscado, int numProductos) {
    int posInicial=0, posFinal=numProductos-1;
    while (true) {
        int posMedio=(posInicial+posFinal)/2;
        if (codigosProductos[posMedio]==codigoBuscado) return posMedio;
        if (codigosProductos[posMedio]<codigoBuscado) posInicial=posMedio+1;
        else posFinal=posMedio-1;
        if (posInicial>posFinal) return -1;
    }
}

void armarStocksFinales(int* &stocksFinales, int* stocksIniciales, int* totalIngresos, int* totalEgresos, int numProductos) {
    stocksFinales=new int[CAPACIDAD_PRODUCTOS];
    for (int i=0; i<numProductos; i++) {
        stocksFinales[i]=stocksIniciales[i]+totalIngresos[i]-totalEgresos[i];
    }
}

void armarMontosTotales(double* &montosTotales, double* preciosUnitarios, int* stocksFinales, int numProductos) {
    montosTotales=new double[CAPACIDAD_PRODUCTOS];
    for (int i=0; i<numProductos; i++) {
        montosTotales[i]=preciosUnitarios[i]*stocksFinales[i];
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

void ordenarCatYStockFinalPorSeleccion(char *categorias, int *codigosProductos, int *stocksIniciales, int* totalIngresos,
    int* totalEgresos, double* preciosUnitarios, int* stocksFinales, double* montosTotales, int numProductos) {

    for (int i=0; i<(numProductos-1); i++) {
        int pos=i;

        for (int j=i+1; j<numProductos; j++) {
            if (categorias[j]<categorias[pos] or
                (categorias[j]==categorias[pos] and stocksFinales[j]>stocksFinales[pos])) {
                pos=j;
            }
        }

        if (pos!=i) {
            intercambiarChar(categorias[i], categorias[pos]);
            intercambiarInt(codigosProductos[i], codigosProductos[pos]);
            intercambiarInt(stocksIniciales[i], stocksIniciales[pos]);
            intercambiarInt(totalIngresos[i], totalIngresos[pos]);
            intercambiarInt(totalEgresos[i], totalEgresos[pos]);
            intercambiarInt(stocksFinales[i], stocksFinales[pos]);
            intercambiarDouble(preciosUnitarios[i], preciosUnitarios[pos]);
            intercambiarDouble(montosTotales[i], montosTotales[pos]);
        }
    }
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}


void imprimirEncabezadoRepSimple(ofstream &salida) {
    salida << "LISTADO DE PRODUCTOS ORDENADOS ASCENDENTEMENTE POR CODIGO" << endl;
    salida << right << setw(9) << "CODIGO" << setw(11) << "CATEGORIA" << setw(15) << "STOCK INICIAL"
            << setw(10) << "PRECIO" << endl;
}

void imprimirEncabezadoKardex(ofstream &salida) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << right << setw(70) << "KARDEX DE PRODUCTOS" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << "CATEGORIA" << right << setw(10) << "CODIGO" << setw(18) << "STOCK INICIAL" << setw(18) << "TOTAL INGRESOS"
            << setw(18) << "TOTAL EGRESOS" << setw(18) << "STOCK FINAL" << setw(10) << "PRECIO"
            << setw(18) << "MONTO TOTAL" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
}

void generarReporteSimple(const char *nombreArchivo, char *categorias, int *codigosProductos, int *stocksIniciales,
                          double *preciosUnitarios, int numProductos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    imprimirEncabezadoRepSimple(salida);
    for (int i=0; i<numProductos; i++) {
        salida << right << setw(8) << codigosProductos[i] << setw(8) << categorias[i] << setw(13)
            << stocksIniciales[i] << setw(16) << fixed << setprecision(2) << preciosUnitarios[i] << endl;
    }
}

void generarListado(const char *nombreArchivo, char *categorias, int *codigosProductos, int numProductos, int *stocksFinales) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    for (int i=0; i<numProductos; i++) {
        if (stocksFinales[i]==0) salida << categorias[i] << "," << codigosProductos[i] << endl;
    }
}

void generarReporte(const char *nombreArchivo, char *categorias, int *codigosProductos, int *stocksIniciales,
    int *totalIngresos, int *totalEgresos, double *preciosUnitarios, int *stocksFinales, double *montosTotales,
    int numProductos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    imprimirEncabezadoKardex(salida);
    for (int i=0; i<numProductos; i++) {
        if (stocksFinales[i]>0) {
            salida << right << setw(5) << categorias[i] << setw(13) << codigosProductos[i] << setw(13) << stocksIniciales[i]
                << setw(17) << totalIngresos[i] << setw(19) << totalEgresos[i] << setw(21) << stocksFinales[i]
                << setw(14) << fixed << setprecision(2) << preciosUnitarios[i] << setw(17) << montosTotales[i] << endl;
        }
    }
}
