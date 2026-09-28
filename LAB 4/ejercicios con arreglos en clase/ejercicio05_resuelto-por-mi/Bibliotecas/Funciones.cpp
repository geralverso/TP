//
// Created by PC on 27/09/2026.
//

#include "Funciones.h"

void cargarVentasCSV(const char *nombreArchivo, int *codigosVentas, int *cantidadesVentas, int &numVentas) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    numVentas=0;
    int codigoVenta, cantVenta;
    char c;
    while (entrada>>codigoVenta) {
        entrada >> c >> cantVenta;
        codigosVentas[numVentas]=codigoVenta;
        cantidadesVentas[numVentas]=cantVenta;
        numVentas++;
    }
}

void cargarProductosCSV(const char *nombreArchivo, int *codigosProductos, char *categoriasProductos,
    double *preciosProductos, int *sotcksProductos, bool *importadosProductos, int &numProductos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    numProductos=0;
    int codigoProducto, stockInicial;
    char c, categoria;
    bool importado;
    double precio;
    while (entrada>>codigoProducto) {
        entrada >> c >> categoria >> c >> precio >> c >> stockInicial >> c >> importado;
        codigosProductos[numProductos]=codigoProducto;
        categoriasProductos[numProductos]=categoria;
        preciosProductos[numProductos]=precio;
        sotcksProductos[numProductos]=stockInicial;
        importadosProductos[numProductos]=importado;
        numProductos++;
    }
}

void separador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void encabezado1(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "DETALLE DE VENTAS" << endl;
    separador(salida, '=', ANCHO);
    salida << left << setw(8) << "  Nro" << setw(8) << "Codigo" << setw(10) << "Cantidad" << "Estado" << endl;
    separador(salida, '-', ANCHO);
}

void encabezado2(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "VENTAS POR PRODUCTO" << endl;
    separador(salida, '=', ANCHO);
    salida << right << setw(8) << "Codigo" << setw(10) << "Precio" << setw(10) << "Vendidas" << setw(12) << "Ingreso"
            << setw(13) << "Stock final" << endl;
    separador(salida, '-', ANCHO);
}

void encabezado3(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << "RESUMEN" << endl;
    separador(salida, '=', ANCHO);
}

int buscarPosCodigoVentaEnProductosCSV(int codigoBuscado, int *codigosProductos, int numProductos) {
    for (int i=0; i<numProductos; i++) {
        if (codigosProductos[i]==codigoBuscado) {
            return i;
        }
    }
    return -1;
}

void detalleDeVentas(ofstream &salida, int *codigosVentas, int *cantidadesVentas, int numVentas, int *codigosProductos,
    int *stocksProductos, int numProductos, int *cantProductosVendidos, double *ingresoProductosVendidos,
    double *preciosProductos, int &cantVentasAtendidasTotales, int &cantVentasSinStockTotales,
    int &cantVentasProdNoRegisTotales) {

    encabezado1(salida);
    for (int i=0; i<numVentas; i++) {
        int codigoVenta=codigosVentas[i];
        int cantidadVenta=cantidadesVentas[i];
        salida << right << setw(5) << (i+1) << setw(9) << codigoVenta << setw(10) << cantidadVenta << "  ";

        int posicion=buscarPosCodigoVentaEnProductosCSV(codigoVenta, codigosProductos, numProductos);
        if (posicion>=0) {
            if (cantidadesVentas[i]>stocksProductos[posicion]) {
                salida << "Stock insuficiente" << endl;
                cantVentasSinStockTotales++;
            }
            else {
                salida << "Atendida" << endl;
                stocksProductos[posicion]-=cantidadesVentas[i]; //EL STOCK SE ACTUALIZA LUEGO DE CADA VENTA
                cantProductosVendidos[posicion]+=cantidadesVentas[i]; //CANT PRODUCTOS VENDIDOS SE ACTUALIZA LUEGO DE CADA VENTA
                ingresoProductosVendidos[posicion]+=(cantidadesVentas[i]*preciosProductos[posicion]); //EL INGRESO SE ACTUALIZA LUEGO DE CADA VENTA
                cantVentasAtendidasTotales++;
            }
        }
        else {
            salida << "Producto no registrado" << endl;
            cantVentasProdNoRegisTotales++;
        }
    }
}

int buscarPosCodigoProductoMasVendido(int *cantProductosVendidos, int numProductos) {
    if (numProductos==0) return -1;
    int posMasVendido=0;
    for (int i=0;i<numProductos;i++) {
        if (cantProductosVendidos[i]>cantProductosVendidos[posMasVendido]) {
            posMasVendido= i;
        }
    }
    return posMasVendido;
}

int buscarPosCodigoProductoMayorIngreso(double *ingresoProductosVendidos, int numProductos) {
    if (numProductos==0) return -1;
    int posMayorIngreso=0;
    for (int i=0;i<numProductos;i++) {
        if (ingresoProductosVendidos[i]>ingresoProductosVendidos[posMayorIngreso]) {
            posMayorIngreso= i;
        }
    }
    return posMayorIngreso;
}

void ventasPorProducto(ofstream &salida, int numProductos, int *codigosProductos, double *preciosProductos,
    int *cantProductosVendidos, double *ingresoProductosVendidos, int *stocksProductos, int &cantProdSinVentas,
    double &ingresoTotal) {
    encabezado2(salida);
    for (int i=0; i<numProductos; i++) {
        int codigoProducto=codigosProductos[i];
        double precio=preciosProductos[i];
        int cantVentas=cantProductosVendidos[i];
        double ingreso=ingresoProductosVendidos[i];
        int stock=stocksProductos[i];
        salida << right << setw(8) << codigoProducto << setw(10) << fixed << setprecision(2) << precio
                << setw(10) << cantVentas << setw(12) << ingreso << setw(13) << stock << endl;
        if (cantVentas==0) cantProdSinVentas++;
        ingresoTotal+=ingreso;
    }
}

void resumen(ofstream &salida, int *codigosProductos, int numProductos, int *cantProductosVendidos,
    double *ingresoProductosVendidos, int cantVentasAtendidasTotales, int cantVentasSinStockTotales,
    int cantVentasProdNoRegisTotales, int cantProdSinVentas, double ingresoTotal) {
    encabezado3(salida);
    salida << left << setw(40) << "Ventas atendidas: " << right << setw(15) << cantVentasAtendidasTotales << endl;
    salida << left << setw(40) << "Ventas sin stock: " << right << setw(15) << cantVentasSinStockTotales << endl;
    salida << left << setw(40) << "Ventas no registradas: " << right << setw(15) << cantVentasProdNoRegisTotales << endl;
    salida << left << setw(40) << "Ingreso total: " << right << setw(15) << ingresoTotal << endl;
    salida << left << setw(40) << "Productos sin ventas: " << right << setw(15) << cantProdSinVentas << endl;

    salida << left << setw(40) << "Mas vendido (unidades): ";
    int posicionMasVendido=buscarPosCodigoProductoMasVendido(cantProductosVendidos, numProductos);
    if (posicionMasVendido!=-1) {
        salida << right << setw(15) << cantProductosVendidos[posicionMasVendido] << endl;
        salida << "  producto " << codigosProductos[posicionMasVendido] << endl;
    }
    salida << left << setw(40) << "Mayor ingreso: ";
    int posicionMayorIngreso=buscarPosCodigoProductoMayorIngreso(ingresoProductosVendidos, numProductos);
    if (posicionMayorIngreso!=-1) {
        salida << right << setw(15) << ingresoProductosVendidos[posicionMayorIngreso] << endl;
        salida << "  producto " << codigosProductos[posicionMayorIngreso] << endl;
    }
}

void generarReporte(const char *nombreArchivo, int *codigosVentas, int *cantidadesVentas, int numVentas,
    int *codigosProductos, double *preciosProductos, int *stocksProductos, int numProductos, int *cantProductosVendidos,
    double *ingresoProductosVendidos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    int cantVentasAtendidasTotales=0, cantVentasSinStockTotales=0, cantVentasProdNoRegisTotales=0, cantProdSinVentas=0;
    double ingresoTotal=0.0;

    //1RA PARTE DEL REPORTE:
    detalleDeVentas(salida, codigosVentas, cantidadesVentas, numVentas, codigosProductos, stocksProductos,
    numProductos, cantProductosVendidos, ingresoProductosVendidos, preciosProductos, cantVentasAtendidasTotales,
    cantVentasSinStockTotales,cantVentasProdNoRegisTotales);

    //2DA PARTE DEL REPORTE:
    ventasPorProducto(salida, numProductos, codigosProductos, preciosProductos, cantProductosVendidos,
        ingresoProductosVendidos, stocksProductos, cantProdSinVentas, ingresoTotal);

    //3RA PARTE DEL REPORTE:
    resumen(salida, codigosProductos, numProductos, cantProductosVendidos, ingresoProductosVendidos,
        cantVentasAtendidasTotales, cantVentasSinStockTotales, cantVentasProdNoRegisTotales, cantProdSinVentas,
        ingresoTotal);

    separador(salida, '=', ANCHO);
}
