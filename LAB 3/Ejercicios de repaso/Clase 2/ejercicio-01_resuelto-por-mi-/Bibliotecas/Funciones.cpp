//
// Created by PC on 18/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos(ifstream &mov, ifstream &prod, ofstream &salida) {
    mov.open("ArchivosDeDatos/movimientos.csv", ios::in);
    prod.open("ArchivosDeDatos/productos.csv", ios::in);
    salida.open("ArchivosDeReportes/reporte.txt", ios::out);
    return mov.is_open() && prod.is_open() && salida.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezado(ofstream &salida) {
    separador(salida, '-', ANCHO);
    salida << "REPORTE DE STOCK POR PRODUCTO" << endl;
    separador(salida, '-', ANCHO);
}

void buscarMovimientosProducto(ifstream &movi, ofstream &salida, int IDproducto, int &stock, int &cantEntradasProducto,
    int &cantSalidasProducto) {
    int ID, cantidad;
    char c, tipo;

    //acá siempre se coloca:
    movi.clear();
    movi.seekg(0, ios::beg);

    while (movi >> ID) {
        movi >> c >> tipo >> c >> cantidad;
        if (ID == IDproducto) {
            if (tipo == 'E') cantEntradasProducto+=cantidad;
            else cantSalidasProducto+=cantidad;
            stock=cantEntradasProducto-cantSalidasProducto;
        }
    }
}

void resumen(ofstream &salida, int cantProductosProcesados, int cantProductosSinMov, int cantEntradasTotales,
    int cantSalidasTotales, int IDproductoConMayorStock, int mayorStock) {
    salida << left << setw(35) << "Productos procesados: " << right << setw(8) << cantProductosProcesados << endl;
    salida << left << setw(35) << "Productos sin movimientos: " << right << setw(8) << cantProductosSinMov << endl;
    salida << left << setw(35) << "Total de entradas: " << right << setw(8) << cantEntradasTotales << endl;
    salida << left << setw(35) << "Total de salidas: " << right << setw(8) << cantSalidasTotales << endl;
    salida << left << setw(35) << "Producto con mayor stock: " << right << setw(8) << IDproductoConMayorStock << endl;
    salida << left << setw(35) << "  stock de ese producto: " << right << setw(8) << mayorStock << endl;
    separador(salida, '-', ANCHO);
}

void generarReporte(ifstream &movi, ifstream &prod, ofstream &salida) {

    encabezado(salida);

    int IDproducto, cantProductosProcesados=0, cantProductosSinMov=0, cantEntradasTotales=0, cantSalidasTotales=0;
    int stock, IDproductoConMayorStock=0, mayorStock=-1;
    char c, categoria;

    while (prod >> IDproducto) {
        prod >> c >> categoria;

        cantProductosProcesados++;
        int cantEntradasProducto=0, cantSalidasProducto=0;

        salida << "Producto " << IDproducto << " (categoria " << categoria << ")" << endl;

        buscarMovimientosProducto(movi,salida, IDproducto, stock, cantEntradasProducto,
            cantSalidasProducto);

        if (cantEntradasProducto==0 and cantSalidasProducto==0) {
            salida << "    sin movimientos registrados" << endl;
            cantProductosSinMov++;
            stock=0;
        }

        salida << left << setw(25) << "  Entradas: " << right << setw(5) << cantEntradasProducto << endl;
        salida << left << setw(25) << "  Salidas: " << right << setw(5) << cantSalidasProducto << endl;
        salida << left << setw(25) << "  Stock resultante: " << right << setw(5) << stock << endl;
        separador(salida, '-', ANCHO);

        //ACUMULADORES PARA EL RESUMEN:
        cantEntradasTotales+=cantEntradasProducto;
        cantSalidasTotales+=cantSalidasProducto;
        if (mayorStock<stock) {
            mayorStock=stock;
            IDproductoConMayorStock=IDproducto;
        }
    }
    resumen(salida, cantProductosProcesados,  cantProductosSinMov, cantEntradasTotales, cantSalidasTotales,
        IDproductoConMayorStock, mayorStock);
}

void cerrarArchivos(ifstream &movi, ifstream &prod, ofstream &salida) {
    movi.close();
    prod.close();
    salida.close();
}
