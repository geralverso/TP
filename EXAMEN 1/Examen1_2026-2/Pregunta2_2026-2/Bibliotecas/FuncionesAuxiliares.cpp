//
// Created by PC on 16/10/2026.
//

#include "FuncionesAuxiliares.h"

bool abrirArchivos(ifstream &cat, ifstream &prod, ofstream &salida) {
    cat.open("ArchivosDeDatos/categorias.csv");
    prod.open("ArchivosDeDatos/productos.csv");
    salida.open("ArchivosDeReporte/ReporteInventarioPorCategoria.txt");
    return cat.is_open() and prod.is_open() and salida.is_open();
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void leerEImprimirNombre(ifstream &entrada, ofstream &salida, bool seMuestra) {
    char c;
    while (true) {
        c=entrada.get();
        if (c=='\n') break;
        if (seMuestra==true) salida << c;
    }
    if (seMuestra==true) salida << endl;
}

void buscarProductos(ifstream &prod, ofstream &salida, char categoria, int &cantProductos, int &cantProdSinStock,
    int &codProdMayorPrecio, int &codProdMenorPrecio, double &valorTotalInventario, double &mayorPrecio,
    double &menorPrecio){
    int codigoProd, stockInicial;
    char cat, c;
    double precioUnitario;
    prod.clear();
    prod.seekg(0);
    while (prod >> codigoProd) {
        prod >> c >> cat >> c >> stockInicial >> c >> precioUnitario >> c;
        if (cat==categoria) {
            double valorInventario=precioUnitario*stockInicial;
            salida << left << setw(7) << codigoProd << right << setw(6) << stockInicial << setw(11) << fixed
                << setprecision(2) << precioUnitario << setw(18) << valorInventario << setw(4) << "";
            leerEImprimirNombre(prod, salida, true);

            cantProductos++;
            valorTotalInventario+=valorInventario;
            if (stockInicial==0) cantProdSinStock++;
            if (mayorPrecio<precioUnitario) {
                mayorPrecio=precioUnitario;
                codProdMayorPrecio=codigoProd;
            }
            if (menorPrecio>precioUnitario) {
                menorPrecio=precioUnitario;
                codProdMenorPrecio=codigoProd;
            }
        }
        else leerEImprimirNombre(prod, salida, false);
    }
}

void buscarCategoria(ifstream &cat, ofstream &salida, char categoriaMayorValorInv) {
    char c, categoria;
    cat.clear();
    cat.seekg(0);
    while (cat >> categoria >> c) {
        if (categoria==categoriaMayorValorInv) leerEImprimirNombre(cat, salida, true);
        else leerEImprimirNombre(cat, salida, false);
    }
}

void imprimirEncabezado(ofstream &salida) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << setw(20) << " " << "REPORTE DE INVENTARIO POR CATEGORIA" << endl;
}

void imprimirTituloPorCategoria(ofstream &salida, ifstream &cat, char categoria) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << left << setw(11) << "CATEGORÍA: " << categoria << " - ";
    leerEImprimirNombre(cat, salida, true);
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << left << setw(8) << "CÓDIGO" << right << setw(6) << "STOCK" << setw(11) << "PRECIO"
            << setw(18) << "VALOR INVENTARIO" << setw(4) << "" << left << setw(38) << "DESCRIPCIÓN" << endl;
}

void imprimirResumenPorCategoria(ofstream &salida, int cantProductos, int cantProdSinStock, double valorTotalInventario,
    int codProdMayorPrecio, double mayorPrecio, int codProdMenorPrecio, double menorPrecio) {
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << left << setw(30) << "Cantidad de productos" << right << setw(20) << cantProductos << endl;
    salida << left << setw(30) << "Productos sin stock" << right << setw(20) << cantProdSinStock << endl;
    salida << left << setw(30) << "Valor total del inventario" << right << setw(20) << fixed << setprecision(2)
            << valorTotalInventario << endl;
    salida << left << setw(30) << "Producto de mayor precio" << right << setw(8) << codProdMayorPrecio << setw(12)
            << mayorPrecio << endl;
    salida << left << setw(30) << "Producto de menor precio" << right << setw(8) << codProdMenorPrecio << setw(12)
            << menorPrecio << endl;
}

void imprimirResumenGeneral(ofstream &salida, ifstream &cat, int cantTotalProductos, int cantTotalProdSinStock,
    double valorTotalInventarioCompleto, char categoriaMayorValorInv, double mayorValorTotalInventario) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << "RESUMEN GENERAL" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << left << setw(42) << "Total de productos" << right << setw(18) << cantTotalProductos << endl;
    salida << left << setw(42) << "Total de productos sin stock" << right << setw(18) << cantTotalProdSinStock << endl;
    salida << left << setw(42) << "Valor total del inventario" << right << setw(18) << fixed << setprecision(2)
            << valorTotalInventarioCompleto << endl;
    salida << left << setw(42) << "Categoría con mayor valor de inventario" << right << categoriaMayorValorInv << " - ";
    buscarCategoria(cat, salida, categoriaMayorValorInv);
    salida << left << setw(42) << "Valor de inventario de la categoría" << right << setw(18) << fixed << setprecision(2)
                << mayorValorTotalInventario << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
}

void generarReporte(ifstream &cat, ifstream &prod, ofstream &salida) {
    imprimirEncabezado(salida);
    char categoria, categoriaMayorValorInv, c;
    int cantTotalProductos=0, cantTotalProdSinStock=0;
    double mayorValorTotalInventario=-1.0, valorTotalInventarioCompleto=0.0;

    while (cat >> categoria >> c) {
        imprimirTituloPorCategoria(salida, cat, categoria);
        int cantProductos=0, cantProdSinStock=0, codProdMayorPrecio=0, codProdMenorPrecio=0;
        double valorTotalInventario=0.0, mayorPrecio=-1.0, menorPrecio=99999.99;
        buscarProductos(prod, salida, categoria, cantProductos, cantProdSinStock, codProdMayorPrecio,
            codProdMenorPrecio, valorTotalInventario, mayorPrecio, menorPrecio);
        imprimirResumenPorCategoria(salida, cantProductos, cantProdSinStock, valorTotalInventario, codProdMayorPrecio,
            mayorPrecio, codProdMenorPrecio, menorPrecio);

        cantTotalProductos+=cantProductos;
        cantTotalProdSinStock+=cantProdSinStock;
        valorTotalInventarioCompleto+=valorTotalInventario;
        if (mayorValorTotalInventario<valorTotalInventario) {
            mayorValorTotalInventario=valorTotalInventario;
            categoriaMayorValorInv=categoria;
        }
    }
    imprimirResumenGeneral(salida, cat, cantTotalProductos, cantTotalProdSinStock, valorTotalInventarioCompleto,
        categoriaMayorValorInv, mayorValorTotalInventario);
}

void cerrarArchivos(ifstream &cat, ifstream &prod, ofstream &salida) {
    cat.close();
    prod.close();
    salida.close();
}