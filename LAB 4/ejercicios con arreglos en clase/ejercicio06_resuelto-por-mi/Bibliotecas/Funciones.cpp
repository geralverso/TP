//
// Created by PC on 28/09/2026.
//

#include "Funciones.h"

void cargarNuevosCSV(const char *nombreArchivo, int *codigosNuevos, char *categoriasDeNuevos, double *preciosNuevos,
    int *stocksNuevos, bool *importadosNuevos, int &numNuevos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numNuevos=0;
    int codigoNuevoProd, stockNuevoProd;
    char c, categoriaNuevoProd;
    double precioNuevoProd;
    bool importadoNuevoProd;
    while (entrada >> codigoNuevoProd) {
        entrada >> c >> categoriaNuevoProd >> c >> precioNuevoProd >> c >> stockNuevoProd >> c >> importadoNuevoProd;
        //LOS PRODUCTOS VIENEN ORDENADOS POR CODIGO
        codigosNuevos[numNuevos]=codigoNuevoProd;
        categoriasDeNuevos[numNuevos]=categoriaNuevoProd;
        preciosNuevos[numNuevos]=precioNuevoProd;
        stocksNuevos[numNuevos]=stockNuevoProd;
        importadosNuevos[numNuevos]=importadoNuevoProd;
        numNuevos++;
    }
}

void cargarProductosCSV(const char *nombreArchivo, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    numProductos=0;
    int codigoProd, stockProd;
    char c, categoriaProd;
    double precioProd;
    bool importadoProd;
    while (entrada >> codigoProd) {
        entrada >> c >> categoriaProd >> c >> precioProd >> c >> stockProd >> c >> importadoProd;
        //LOS PRODUCTOS VIENEN DESORDENADOS POR CODIGO
        insertarOrdenado(codigosProductos, categoriasDeProductos, preciosProductos, stocksProductos, importadosProductos,
            codigoProd, categoriaProd,  precioProd, stockProd, importadoProd,numProductos, CAPACIDAD_PRODUCTOS);
    }
}

int buscarPosicionProductoQueYaExisteEnProductosCSV(int *codigosProductos, int codigoBuscado, int numProductos) {
    if (numProductos==0) return -1;
    for (int i=0; i<numProductos; i++) {
        if (codigosProductos[i]==codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int buscarPosicionOrdenadaParaProductosCSV(int *codigosProductos, int codigoProdNuevo, int numProductos) {
    for (int i=0; i<numProductos; i++) {
        if (codigosProductos[i]>codigoProdNuevo) { //PARA QUE EL INSERTAR ORDENADO SEA DE MENOR A MAYOR
            return i;
        }
    }
    return numProductos;
}

int insertarOrdenado(int *codigosProductos, char *categoriasDeProductos, double *preciosProductos, int *stocksProductos,
    bool *importadosProductos, int codigoProdNuevo, char catProdNuevo, double precioProdNuevo, int stockProdNuevo,
    bool importadoProdNuevo, int &numProductos, int capacidad) {

    //VERIFICAR SI HAY PRODUCTOS REPETIDOS EN nuevos.csv Y productos.csv
    int posicionProdRepetido=buscarPosicionProductoQueYaExisteEnProductosCSV(codigosProductos, codigoProdNuevo,
        numProductos);
    if (posicionProdRepetido!=-1) return -1; //si existe una posicion, no se considera

    //VERIFICAR LA CAPACIDAD
    if (numProductos>=capacidad) return -1;

    //SE HALLA LA POSICION ORDENADA CORRECTA
    //int posicionOrdenada=buscarPosicionOrdenadaParaProductosCSV(codigosProductos, codigoProdNuevo, numProductos);

    //SE DESPLAZAN LOS ELEMENTOS DE ATRÁS HACIA ADELANTE
    // for (int i=numProductos; i>posicionOrdenada; i--) {
    //     codigosProductos[i]=codigosProductos[i-1];
    //     categoriasDeProductos[i]=categoriasDeProductos[i-1];
    //     preciosProductos[i]=preciosProductos[i-1];
    //     stocksProductos[i]=stocksProductos[i-1];
    //     importadosProductos[i]=importadosProductos[i-1];
    // }

    //SE INSERTAN LOS NUEVOS DATOS EN LA POSICION CORRESPONDIENTE
    // codigosProductos[posicionOrdenada]=codigoProdNuevo;
    // categoriasDeProductos[posicionOrdenada]=catProdNuevo;
    // preciosProductos[posicionOrdenada]=precioProdNuevo;
    // stocksProductos[posicionOrdenada]=stockProdNuevo;
    // importadosProductos[posicionOrdenada]=importadoProdNuevo;
    // numProductos++; //SE INCREMENTA EL NUMERO DE PRODUCTOS PQ YA SE INCLUYERON LOS NUEVOS

    int i=numProductos-1;
    while (i>=0 and codigosProductos[i]>codigoProdNuevo) {
        codigosProductos[i+1]=codigosProductos[i];
        categoriasDeProductos[i+1]=categoriasDeProductos[i];
        preciosProductos[i+1]=preciosProductos[i];
        stocksProductos[i+1]=stocksProductos[i];
        importadosProductos[i+1]=importadosProductos[i];
        i--;
    }

    codigosProductos[i+1]=codigoProdNuevo;
    categoriasDeProductos[i+1]=catProdNuevo;
    preciosProductos[i+1]=precioProdNuevo;
    stocksProductos[i+1]=stockProdNuevo;
    importadosProductos[i+1]=importadoProdNuevo;
    numProductos++;

    return i+1;

    //return posicionOrdenada; //en vez de retornar true
}

int buscarPosicionProdMayorPrecioEnProductosCSV(double *preciosProductos, int numProductos, char *categoriasDeProductos,
    char categoriaBuscada) {
    if (numProductos==0) return -1;
    int posicionMayorPrecio=-1;
    for (int i=0; i<numProductos; i++) {
        if (categoriasDeProductos[i]==categoriaBuscada) {
            if (posicionMayorPrecio==-1 or preciosProductos[i]>preciosProductos[posicionMayorPrecio]) {
                posicionMayorPrecio=i;
            }
        }
    }
    return posicionMayorPrecio;
}

void separador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void encabezado1(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "INSERCION DE PRODUCTOS NUEVOS" << endl;
    separador(salida, '=', ANCHO);
}

void encabezado2(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "PRODUCTOS ORDENADOS POR CODIGO" << endl;
    separador(salida, '=', ANCHO);
    salida << right << setw(5) << "Pos" << setw(8) << "Codigo" << setw(5) << "Cat" << setw(10) << "Precio"
            << setw(8) << "Stock" << right << setw(2) << " " << "Importado" << endl;
    separador(salida, '-', ANCHO);
}

void encabezado3(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "RESUMEN POR CATEGORIA" << endl;
    separador(salida, '=', ANCHO);
    salida << right << setw(5) << "Cat" << setw(11) << "Productos" << setw(10) << "Unidades" << setw(11) << "Valor"
            << setw(14) << "Prom.precio" << setw(11) << "Mas caro" << endl;
    separador(salida, '-', ANCHO);
}

void insersionDeProductosNuevos(ofstream &salida, int numNuevos, int *codigosNuevos, char *categoriasDeNuevos,
    double *preciosNuevos, int *stocksNuevos, bool *importadosNuevos, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos) {
    encabezado1(salida);
    for (int i=0; i<numNuevos; i++) {
        //INSERSION DE PRODUCTOS NUEVOS CON INSERTAR ORDENADO
        int codigoProdNuevo=codigosNuevos[i];
        char catProdNuevo=categoriasDeNuevos[i];
        double precioProdNuevo=preciosNuevos[i];
        int stockProdNuevo=stocksNuevos[i];
        bool importadoProdNuevo=importadosNuevos[i];

        int posicionOrdenada=insertarOrdenado(codigosProductos, categoriasDeProductos, preciosProductos, stocksProductos,
            importadosProductos, codigoProdNuevo, catProdNuevo,  precioProdNuevo, stockProdNuevo, importadoProdNuevo,
            numProductos, CAPACIDAD_PRODUCTOS);

        salida << "Producto " << codigoProdNuevo << ": ";
        if (posicionOrdenada>=0) salida << "insertado en la posicion " << posicionOrdenada << endl;
        else salida << "rechazado, el codigo ya existe" << endl;
    }
}

void productosOrdenadosPorCodigo(ofstream &salida, int numProductos, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &cantProductosA, int &cantUnidadesA,
    double &valorUnidadesA, double &sumaPreciosA, int &cantProductosB, int &cantUnidadesB, double &valorUnidadesB,
    double &sumaPreciosB, int &cantProductosC, int &cantUnidadesC, double &valorUnidadesC, double &sumaPreciosC,
    int &cantProductosD, int &cantUnidadesD, double &valorUnidadesD, double &sumaPreciosD) {
    encabezado2(salida);
    for (int i=0; i<numProductos; i++) {
        int posicion=i;
        int codigo=codigosProductos[i];
        char categoria=categoriasDeProductos[i];
        double precio=preciosProductos[i];
        int stock=stocksProductos[i];
        bool importado=importadosProductos[i];
        salida << right << setw(5) << posicion << setw(8) << codigo << setw(5) << categoria << setw(10) << fixed
                << setprecision(2) << precio << setw(8) << stock << right << setw(2) << " ";
        if (importado==0) salida << "No" << endl;
        else salida << "Si" << endl;
        if (categoria=='A') {
            cantProductosA++;
            cantUnidadesA+=stock;
            valorUnidadesA+=(stock*precio);
            sumaPreciosA+=precio;
        }
        if (categoria=='B') {
            cantProductosB++;
            cantUnidadesB+=stock;
            valorUnidadesB+=(stock*precio);
            sumaPreciosB+=precio;
        }
        if (categoria=='C') {
            cantProductosC++;
            cantUnidadesC+=stock;
            valorUnidadesC+=(stock*precio);
            sumaPreciosC+=precio;
        }
        if (categoria=='D') {
            cantProductosD++;
            cantUnidadesD+=stock;
            valorUnidadesD+=(stock*precio);
            sumaPreciosD+=precio;
        }
    }
}

void lineaDeDatosPorCategoria(ofstream &salida, char categoria, int cantProductos, int cantUnidades, double valor,
    double promPrecio, int *codigosProductos, char *categoriasDeProductos, double *preciosProductos, int numProductos) {
    salida << right << setw(5) << categoria << setw(11) << cantProductos << setw(10) << cantUnidades << setw(11)
            << fixed << setprecision(2) << valor << setw(14) << fixed << setprecision(2) << promPrecio;
    int posicion=buscarPosicionProdMayorPrecioEnProductosCSV(preciosProductos, numProductos, categoriasDeProductos, categoria);
    if (posicion!=-1) salida << setw(11) << codigosProductos[posicion] << endl;
}

void resumenPorCategoria(ofstream &salida, int *codigosProductos, char *categoriasDeProductos, double *preciosProductos,
    int numProductos, int cantProductosA, int cantUnidadesA, double valorUnidadesA, double sumaPreciosA, int cantProductosB,
    int cantUnidadesB, double valorUnidadesB, double sumaPreciosB, int cantProductosC, int cantUnidadesC, double valorUnidadesC,
    double sumaPreciosC, int cantProductosD, int cantUnidadesD, double valorUnidadesD, double sumaPreciosD){

    double promPrecioA=(cantProductosA>0)?(sumaPreciosA/cantProductosA):0.0;
    double promPrecioB=(cantProductosB>0)?(sumaPreciosB/cantProductosB):0.0;
    double promPrecioC=(cantProductosC>0)?(sumaPreciosC/cantProductosC):0.0;
    double promPrecioD=(cantProductosD>0)?(sumaPreciosD/cantProductosD):0.0;
    encabezado3(salida);
    lineaDeDatosPorCategoria(salida, 'A', cantProductosA, cantUnidadesA, valorUnidadesA,
    promPrecioA, codigosProductos, categoriasDeProductos, preciosProductos, numProductos);
    lineaDeDatosPorCategoria(salida, 'B', cantProductosB, cantUnidadesB, valorUnidadesB,
    promPrecioB, codigosProductos, categoriasDeProductos, preciosProductos, numProductos);
    lineaDeDatosPorCategoria(salida, 'C', cantProductosC, cantUnidadesC, valorUnidadesC,
    promPrecioC, codigosProductos, categoriasDeProductos, preciosProductos, numProductos);
    lineaDeDatosPorCategoria(salida, 'D', cantProductosD, cantUnidadesD, valorUnidadesD,
        promPrecioD, codigosProductos, categoriasDeProductos, preciosProductos, numProductos);
    separador(salida,'-', ANCHO);

    char categoriaMayorValor='A';
    double mayorValor=valorUnidadesA;
    if (valorUnidadesB>mayorValor) {
        mayorValor=valorUnidadesB;
        categoriaMayorValor='B';
    }
    else if (valorUnidadesC>mayorValor) {
        mayorValor=valorUnidadesC;
        categoriaMayorValor='C';
    }
    else if (valorUnidadesD>mayorValor) {
        mayorValor=valorUnidadesD;
        categoriaMayorValor='D';
    }
    salida << "Categoria con mayor valor de inventario: " << categoriaMayorValor << " (" << fixed << setprecision(2)
            << mayorValor << ")" << endl;
}

void generarReporte(const char *nombreArchivo, int *codigosNuevos, char *categoriasDeNuevos, double *preciosNuevos,
    int *stocksNuevos, bool *importadosNuevos, int numNuevos, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    insersionDeProductosNuevos(salida, numNuevos, codigosNuevos, categoriasDeNuevos, preciosNuevos, stocksNuevos,
        importadosNuevos, codigosProductos, categoriasDeProductos, preciosProductos, stocksProductos,
        importadosProductos, numProductos);

    int cantProductosA=0, cantProductosB=0, cantProductosC=0, cantProductosD=0;
    int cantUnidadesA=0, cantUnidadesB=0, cantUnidadesC=0, cantUnidadesD=0;
    double valorUnidadesA=0.0, valorUnidadesB=0.0, valorUnidadesC=0.0, valorUnidadesD=0.0;
    double sumaPreciosA=0.0, sumaPreciosB=0.0, sumaPreciosC=0.0, sumaPreciosD=0.0;
    productosOrdenadosPorCodigo(salida, numProductos, codigosProductos, categoriasDeProductos, preciosProductos,
        stocksProductos, importadosProductos, cantProductosA, cantUnidadesA, valorUnidadesA, sumaPreciosA,
        cantProductosB,cantUnidadesB, valorUnidadesB, sumaPreciosB, cantProductosC, cantUnidadesC,
        valorUnidadesC, sumaPreciosC, cantProductosD, cantUnidadesD, valorUnidadesD, sumaPreciosD);

    resumenPorCategoria(salida, codigosProductos, categoriasDeProductos, preciosProductos, numProductos, cantProductosA,
        cantUnidadesA, valorUnidadesA, sumaPreciosA, cantProductosB,cantUnidadesB, valorUnidadesB, sumaPreciosB,
        cantProductosC, cantUnidadesC, valorUnidadesC, sumaPreciosC, cantProductosD, cantUnidadesD, valorUnidadesD,
        sumaPreciosD);
}
