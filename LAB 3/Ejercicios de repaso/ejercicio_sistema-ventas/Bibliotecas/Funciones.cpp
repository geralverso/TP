//
// Created by PC on 21/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos(ifstream &ventas, ifstream &inven, ifstream &config, ofstream &txt, ofstream &json,
    ofstream &csv) {
    ventas.open("ArchivosDeDatos/ventas.csv");
    inven.open("ArchivosDeDatos/inventario.txt");
    config.open("ArchivosDeDatos/config_tienda.json");
    txt.open("ArchivosDeReportes/reporte_ventas.txt");
    json.open("ArchivosDeReportes/reporte_ventas.json");
    csv.open("ArchivosDeReportes/reporte_ventas.csv");
    return ventas.is_open() && inven.is_open() && config.is_open() and txt.is_open() and json.is_open()
    and csv.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezado(ofstream &txt) {
    separador(txt, '-', ANCHO);
    txt << "REPORTE DE VENTAS EN TXT" << endl;
    separador(txt, '-', ANCHO);
}

void buscarInfoVentas(ifstream &ventas, ofstream &txt, char codigoProducto, int &cantUnidadesVendidasPorProducto,
    double &ingresoTotalPorProducto) {

    while (ventas.peek()=='d') ventas.ignore(1000, '\n');

    int dia, mes, cantidad;
    double precioUnitario, ingreso=0;
    char c, codigo;

    ventas.clear();
    ventas.seekg(49); //porque hay una linea con datos no importantes al inicio en seekg(0) )

    while (ventas >> dia) {
        ventas >> c >> mes >> c >> codigo >> c >> cantidad >> c >> precioUnitario;
        if (codigo==codigoProducto) {
            txt << "   Cantidad: " << left << setw(5) << cantidad << "Precio unitario: "
                    << fixed << setprecision(2) << precioUnitario << endl;
            cantUnidadesVendidasPorProducto+=cantidad;
            ingreso=cantidad*precioUnitario;
            ingresoTotalPorProducto+=ingreso;
        }
    }
}

void escribirEnTXT(ofstream &txt, int cantUnidadesVendidasPorProducto, double ingresoTotalPorProducto,
    int stockRestante, char alerta) {
    txt << "Unidades vendidas: " << cantUnidadesVendidasPorProducto << endl;
    txt << "Ingreso total: " << ingresoTotalPorProducto << endl;
    txt << "Stock restante: " << stockRestante << endl;
    txt << "Alerta de reposición: " << alerta << endl;
    separador(txt, '-', ANCHO);
}

void escribirEnJSON(ofstream &json, char codigoProducto, int cantUnidadesVendidasPorProducto,
    double ingresoTotalPorProducto, int stockRestante, char alerta) {
    json << "{\"producto_" << codigoProducto << "_unidades\": " << cantUnidadesVendidasPorProducto
            << ", \"producto_" << codigoProducto << "_ingreso\": " << fixed << setprecision(2)
            << ingresoTotalPorProducto << ", \"producto_" << codigoProducto << "_stock_restante\": "
            << stockRestante << ", \"producto_" << codigoProducto << "_alerta\": \"" << alerta << "\"}" << endl;
}

void escribirEnTCSV(ofstream &csv, char codigoProducto, int cantUnidadesVendidasPorProducto,
    double ingresoTotalPorProducto, int stockRestante, char alerta) {
    csv << codigoProducto << "," << cantUnidadesVendidasPorProducto << "," << fixed << setprecision(2)
        << ingresoTotalPorProducto << "," << stockRestante << "," << alerta << endl;
}

void resumenTXT(ofstream &txt, double ingresoTotalDeLaTienda, double montoDeImpuesto, double ingresoNeto,
                double porcentajeDeCumpDeMeta, double ingresoPromedioPorEmpleado) {
    txt << "Ingreso total de la tienda: " << ingresoTotalDeLaTienda << endl;
    txt << "Monto de impuesto: " << montoDeImpuesto << endl;
    txt << "Ingreso neto: " << ingresoNeto << endl;
    txt << "Porcentaje de cumplimiento de meta: " << porcentajeDeCumpDeMeta << "%" << endl;
    txt << "Ingreso promedio por empleado: " << ingresoPromedioPorEmpleado << endl;
    separador(txt, '-', ANCHO);
}

void generarReportes(ifstream &ventas, ifstream &inven, ifstream &config, ofstream &txt, ofstream &json,
    ofstream &csv) {

    encabezado(txt);
    int stockActual, stockMinimo, numEmpleados, anioDeApertura, stockRestante=0, cantUnidadesVendidasTotalDeLaTienda=0;
    char codigoProducto, codigoTienda, alerta;
    double ingresoTotalDeLaTienda=0.0, metaVentasMensual, impuesto;

    while (inven >> codigoProducto) {
        inven >> stockActual >> stockMinimo;
        int cantUnidadesVendidasPorProducto=0;
        double ingresoTotalPorProducto=0.0;

        //ESCRIBIMOS EN .txt
        txt << "Producto " << codigoProducto << endl;
        buscarInfoVentas(ventas,txt, codigoProducto, cantUnidadesVendidasPorProducto,
            ingresoTotalPorProducto);
        stockRestante=stockActual-cantUnidadesVendidasPorProducto;
        if (stockRestante<stockMinimo) alerta='S';
        else alerta='N';
        escribirEnTXT(txt, cantUnidadesVendidasPorProducto, ingresoTotalPorProducto, stockRestante, alerta);

        //ESCRIBIMOS EN .json
        escribirEnJSON(json, codigoProducto, cantUnidadesVendidasPorProducto, ingresoTotalPorProducto,
            stockRestante, alerta);

        //ESCRIBIMOS EN .csv
        escribirEnTCSV(csv, codigoProducto, cantUnidadesVendidasPorProducto, ingresoTotalPorProducto, stockRestante,
            alerta);

        cantUnidadesVendidasTotalDeLaTienda+=cantUnidadesVendidasPorProducto;
        ingresoTotalDeLaTienda+=ingresoTotalPorProducto;
    }

    //AHORA A LEER EL .json
    config.ignore(1000, ':');
    config.ignore(1000, '"'); config >> codigoTienda;
    config.ignore(1000, ':'); config >> numEmpleados;
    config.ignore(1000, ':'); config >> metaVentasMensual;
    config.ignore(1000, ':'); config >> impuesto;
    config.ignore(1000, ':'); config >> anioDeApertura;
    config.ignore(1000, '}');
    double montoDeImpuesto=ingresoTotalDeLaTienda*impuesto;
    double ingresoNeto=ingresoTotalDeLaTienda-montoDeImpuesto;
    double porcentajeDeCumpDeMeta=(ingresoTotalDeLaTienda/metaVentasMensual)*100;
    double ingresoPromedioPorEmpleado=ingresoTotalDeLaTienda/numEmpleados;

    resumenTXT(txt, ingresoTotalDeLaTienda, montoDeImpuesto, ingresoNeto,porcentajeDeCumpDeMeta,
        ingresoPromedioPorEmpleado);
    resumenJSON(json, ingresoTotalDeLaTienda, montoDeImpuesto, ingresoNeto,porcentajeDeCumpDeMeta,
        ingresoPromedioPorEmpleado);
    resumenCSV(csv, 'X', cantUnidadesVendidasTotalDeLaTienda, ingresoTotalDeLaTienda, 0, 'N');
}

void resumenJSON(ofstream &json, double ingresoTotalDeLaTienda, double montoDeImpuesto, double ingresoNeto,
    double porcentajeDeCumpDeMeta, double ingresoPromedioPorEmpleado) {
    json << "{\"ingreso_total\": " << fixed << setprecision(2) << ingresoTotalDeLaTienda
        << ", \"monto_impuesto\": " << fixed << setprecision(2) << montoDeImpuesto
        << ", \"ingreso_neto\": " << fixed << setprecision(2) << ingresoNeto
        << ", \"porcentaje_meta\": " << fixed << setprecision(2) << porcentajeDeCumpDeMeta
        << ", \"ingreso_por_empleado\": " << fixed << setprecision(2) << ingresoPromedioPorEmpleado << "}"<< endl;
}

void resumenCSV(ofstream &csv, char codigo, int cantUnidadesVendidasTotalDeLaTienda, double ingresoTotalDeLaTienda,
    int stock, char alerta) {
    csv << codigo << "," << cantUnidadesVendidasTotalDeLaTienda << "," << fixed << setprecision(2)
            << ingresoTotalDeLaTienda << "," << stock << "," << alerta << endl;
}

void cerrarArchivos(ifstream &ventas, ifstream &inven, ifstream &config, ofstream &txt, ofstream &json,
                    ofstream &csv) {
    ventas.close();
    inven.close();
    config.close();
    txt.close();
    json.close();
    csv.close();
}
