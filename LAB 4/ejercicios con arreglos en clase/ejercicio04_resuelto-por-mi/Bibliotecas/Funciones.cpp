//
// Created by PC on 28/09/2026.
//

#include "Funciones.h"

void cargarConsultasTXT(const char *nombreArchivo, int *codigosConsultas, int &numConsultas) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    numConsultas=0;
    int codigoConsulta;
    while (entrada >> codigoConsulta) {
        codigosConsultas[numConsultas]=codigoConsulta;
        numConsultas++;
    }
}

void cargarCategoriasTXT(const char *nombreArchivo, char *categoriasEnCategorias, int &numCategorias) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    numCategorias=0;
    char categoriaConsulta;
    while (entrada >> categoriaConsulta) {
        categoriasEnCategorias[numCategorias]=categoriaConsulta;
        numCategorias++;
    }
}

void cargarProductosCSV(const char *nombreArchivo, int *codigosProductos, char *categoriasProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    numProductos=0;
    int codigoProducto, stockProducto;
    char c, categoriaProducto;
    double precioProducto;
    bool importadoProducto;
    while (entrada >> codigoProducto) {
        entrada >> c >> categoriaProducto >> c >>precioProducto >> c >> stockProducto >> c >> importadoProducto;
        codigosProductos[numProductos]=codigoProducto;
        categoriasProductos[numProductos]=categoriaProducto;
        preciosProductos[numProductos]=precioProducto;
        stocksProductos[numProductos]=stockProducto;
        importadosProductos[numProductos]=importadoProducto;
        numProductos++;
    }
}

void separador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void encabezado1(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "CONSULTAS POR CODIGO" << endl;
    separador(salida, '=', ANCHO);
    salida << right << setw(8) << "Codigo" << setw(6) << "Pos" << setw(5) << "Cat" << setw(10) << "Precio"
            << setw(8) << "Stock" << setw(2) << " " << left << "Estado" << endl;
    separador(salida, '-', ANCHO);
}

void encabezado2(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "MAS BARATO DISPONIBLE POR CATEGORIA" << endl;
    separador(salida, '=', ANCHO);
    salida << right << setw(5) << "Cat" << setw(11) << "Productos" << setw(12) << "Codigo" << setw(6) << "Pos"
            << setw(10) << "Precio" << endl;
    separador(salida, '-', ANCHO);
}

void encabezado3(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "PRODUCTO CON MAYOR STOCK" << endl;
    separador(salida, '=', ANCHO);
}

void encabezado4(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "PRODUCTOS AGOTADOS" << endl;
    separador(salida, '=', ANCHO);
}

int buscarPosicionConsultaEnProductosCSV(int codigoBuscado, int *codigosProductos, int numProductos) {
    for (int i=0; i<numProductos; i++) {
        if (codigosProductos[i] == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int contarProdPorCategoriasEnProductosCSV(char categoriaBuscada, char *categoriasProductos, int numProductos) {
    if (numProductos==0) return 0;
    int cantProductos=0;
    for (int i=0; i<numProductos; i++) {
        if (categoriasProductos[i]==categoriaBuscada) {
            cantProductos++;
        }
    }
    return cantProductos;
}

int buscarPosicionProdMasBaratoEnProductosCSV(char categoriaBuscada, char *categoriasProductos,
    double *preciosProductos, int numProductos, int *stocksProductos) {
    if (numProductos==0) return -1;
    int posicionMasBarato=0; //FUNCIONA CON posicionMasBarato=0 O posicionMasBarato=-1
    for (int i=0; i<numProductos; i++) {            //stocksProductos[i]>0 para q el producto ESTÉ DISPONIBLE
        if (categoriasProductos[i]==categoriaBuscada and stocksProductos[i]>0) {
            if (posicionMasBarato==0 or preciosProductos[i]<preciosProductos[posicionMasBarato]) {
                posicionMasBarato=i;
            }
        }
    }
    return posicionMasBarato;
}

int buscarPosicionMayorStockEnProductosCSV(int *stocksProductos, int numProductos) {
    if (numProductos==0) return -1;
    int posicionMayorStock=0;
    for (int i=0; i<numProductos; i++) {
        if (stocksProductos[i]>stocksProductos[posicionMayorStock]) {
            posicionMayorStock=i;
        }
    }
    return posicionMayorStock;
}

void masBaratoDisponiblePorCat(ofstream &salida, int numCategorias, char *categoriasEnCategorias,
                               char *categoriasProductos, double *preciosProductos, int numProductos, int *stocksProductos,
                               int *codigosProductos) {
    encabezado2(salida);
    for (int i=0; i<numCategorias; i++) {
        char categoria=categoriasEnCategorias[i];
        int cantProductos=contarProdPorCategoriasEnProductosCSV(categoria, categoriasProductos, numProductos);
        salida << right << setw(5) << categoria << setw(11) << cantProductos;

        if (cantProductos==0) {
            salida << "  Sin productos disponibles" << endl;
        }
        else { //BUSCAMOS EL PRODUCTO MAS BARATO
            int posicionMasBarato=buscarPosicionProdMasBaratoEnProductosCSV(categoria, categoriasProductos, preciosProductos,
                numProductos, stocksProductos);
            if (posicionMasBarato!=1) {
                salida << setw(12) << codigosProductos[posicionMasBarato] << setw(6) << posicionMasBarato
                        << setw(10) << fixed << setprecision(2) << preciosProductos[posicionMasBarato] << endl;
            }
        }
    }
}

void consultasPorCodigo(ofstream &salida, int numConsultas, int *codigosConsultas, int *codigosProductos,
    char *categoriasProductos, double *preciosProductos, int *stocksProductos, int numProductos) {
    encabezado1(salida);
    for (int i=0; i<numConsultas; i++) {
        int codigoConsulta=codigosConsultas[i];
        salida << right << setw(8) << codigoConsulta;

        int posicionConsulta=buscarPosicionConsultaEnProductosCSV(codigoConsulta, codigosProductos, numProductos);
        if (posicionConsulta>=0) {
            char categoriaConsulta=categoriasProductos[posicionConsulta];
            double precioConsulta=preciosProductos[posicionConsulta];
            int stockConsulta=stocksProductos[posicionConsulta];
            salida << setw(6) << posicionConsulta << setw(5) << categoriaConsulta << setw(10) << fixed
                    << setprecision(2) << precioConsulta << setw(8) << stockConsulta << "  ";
            if (stockConsulta>0) salida << "Disponible" << endl;
            else salida << "Agotado" << endl;
        }
        else salida << "   No registrado" << endl;
    }
}

void productoConMayorStock(ofstream &salida, int *stocksProductos, int numProductos, int *codigosProductos) {
    encabezado3(salida);
    int posicionMayorStock=buscarPosicionMayorStockEnProductosCSV(stocksProductos, numProductos);
    if (posicionMayorStock!=-1) {
        salida << "Producto " << codigosProductos[posicionMayorStock] << " con " << stocksProductos[posicionMayorStock]
                << " unidades (posicion " << posicionMayorStock << ")" << endl;
    }
}

void productosAgotados(ofstream &salida, int numProductos, int *codigosProductos, int *stocksProductos) {
    encabezado4(salida);
    int cantProductosAgotados=0;
    for (int i=0; i<numProductos; i++) {
        if (stocksProductos[i]==0) {
            salida << "Producto " << codigosProductos[i] << " (posicion " << i << ")" << endl;
            cantProductosAgotados++;
        }
    }
    separador(salida, '-', ANCHO);
    salida << "Total de agotados: " << cantProductosAgotados << endl;
}

void generarReporte(const char *nombreArchivo, int *codigosConsultas, int numConsultas, char *categoriasEnCategorias,
    int numCategorias, int *codigosProductos, char *categoriasProductos, double *preciosProductos, int *stocksProductos,
    bool *importadosProductos, int numProductos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    //1RA PARTE DEL REPORTE:
    consultasPorCodigo(salida, numConsultas, codigosConsultas, codigosProductos, categoriasProductos, preciosProductos,
        stocksProductos, numProductos);

    //2DA PARTE DEL REPORTE:
    masBaratoDisponiblePorCat(salida, numCategorias, categoriasEnCategorias, categoriasProductos, preciosProductos,
        numProductos, stocksProductos, codigosProductos);

    //3RA PARTE DEL REPORTE:
    productoConMayorStock(salida, stocksProductos, numProductos, codigosProductos);

    //4TA PARTE DEL REPORTE:
    productosAgotados(salida, numProductos, codigosProductos, stocksProductos);
}
