//
// Created by PC on 15/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos(ifstream &clientes, ifstream &pedidos, ofstream &salida) {
    clientes.open("ArchivosDeDatos/clientes.csv");
    pedidos.open("ArchivosDeDatos/pedidos.csv");
    salida.open("ArchivosDeReportes/Reporte.txt");
    return clientes.is_open() && pedidos.is_open() && salida.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezado(ofstream &salida) {
    separador(salida,'-', ANCHO_DEL_REPORTE);
    salida << "REPORTE DE PEDIDOS POR CLIENTE" << endl;
    separador(salida,'-', ANCHO_DEL_REPORTE);
}

void infoPedidos(ifstream &pedidos, ofstream &salida, int &cantPedidos, double &totalCostoPedidos,
    int numCliente) {
    char c;
    double costoPedido;
    int numClientePedidos;

    //CUANDO SE VA A RELEER UN ARCHIVO (pedidos.csv) 2 O MÁS VECES SE DECLARA ESTO:
    pedidos.clear();
    pedidos.seekg(0,ios::beg); //tmb se escribe pedidos.seekg(0)

    while (pedidos>>numClientePedidos) {
        pedidos >> c >> costoPedido;
        if (numClientePedidos==numCliente) { //numCliente en pedidos.csv == numCliente en clientes.csv
            salida << setw(4) << " " << "pedido" << right
                << setw(15) << fixed << setprecision(2) << costoPedido << endl;
            cantPedidos++;
            totalCostoPedidos+=costoPedido;
        }
    }
}

void resumenFinal(ofstream &salida, int cantTotalClientes, int cantClientesSinPedidos,
    double TotalDeTotalesCostoPedidos, int numClienteMayorGasto, double mayorCostoTotalPedidos) {
    salida << left << setw(30) << "Clientes procesados: " << right << setw(20) << cantTotalClientes << endl;
    salida << left << setw(30) << "Clientes sin pedidos: " << right << setw(20) << cantClientesSinPedidos << endl;
    salida << left << setw(30) << "Total facturado: " << right << setw(20) << TotalDeTotalesCostoPedidos << endl;
    salida << left << setw(30) << "Cliente con mayor gasto: " << right << setw(20) << numClienteMayorGasto << endl;
    salida << left << setw(30) << "  monto de ese cliente: " << right << setw(20) << mayorCostoTotalPedidos << endl;
    separador(salida,'-', ANCHO_DEL_REPORTE);
}

void generarReporte(ifstream &clientes, ifstream &pedidos, ofstream &salida) {
    encabezado(salida);
    int numCliente;
    char c, categoria;

    //DATOS INICIALES PARA EL RESUMEN FINAL:
    int cantTotalClientes=0, cantClientesSinPedidos=0, numClienteMayorGasto;
    double TotalDeTotalesCostoPedidos=0.0, mayorCostoTotalPedidos=-1.0;

    while (clientes >>numCliente) { //PARA LEER LO DE clientes.csv
        clientes >> c >> categoria;
        salida << "Cliente " << numCliente << " (categoria " << categoria << ")" << endl;

        //DATOS INICIALES PARA infoPedidos:
        int cantPedidos=0;
        double totalCostoPedidos=0.0, promedioCostoPedidos;
        infoPedidos(pedidos,salida,cantPedidos,totalCostoPedidos, numCliente);

        //EL PROMEDIO SE CALCULA DESPUES DE ACUMULAR totalCostoPedidos Y cantPedidos
        promedioCostoPedidos=(cantPedidos>0)?totalCostoPedidos/cantPedidos:0.00;

        if (cantPedidos==0) {
            salida << setw(4) << " " << "sin pedidos registrados" << endl;
            cantClientesSinPedidos++;
        }

        salida << left << setw(15) << "  Pedidos: " << right << setw(15) << cantPedidos << endl;
        salida << left << setw(15) << "  Total: " << right << setw(15)
                << fixed << setprecision(2) << totalCostoPedidos << endl;
        salida << left << setw(15) << "  Promedio: " << right << setw(15)
                << fixed << setprecision(2) << promedioCostoPedidos << endl;
        separador(salida,'-', ANCHO_DEL_REPORTE);

        //SE ACUMULAN LAS VARIABLES PARA EL RESUMEN FINAL:
        cantTotalClientes++;
        TotalDeTotalesCostoPedidos+=totalCostoPedidos;
        if (totalCostoPedidos>mayorCostoTotalPedidos) {
            mayorCostoTotalPedidos=totalCostoPedidos;
            numClienteMayorGasto=numCliente;
        }
    }
    resumenFinal(salida, cantTotalClientes, cantClientesSinPedidos, TotalDeTotalesCostoPedidos,
        numClienteMayorGasto, mayorCostoTotalPedidos);
}

void cerrarArchivos(ifstream &clientes, ifstream &pedidos, ofstream &salida) {
    clientes.close();
    pedidos.close();
    salida.close();
}
