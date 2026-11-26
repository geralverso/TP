//
// Created by PC on 25/11/2026.
//

#include "FuncionesAuxiliares.h"


//FUNCIONES PARA LEER, ACUMULAR, CARGAR, BUSCAR, INSERTAR:

void abrirArchLectura(const char* nombreArch, ifstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void leerPlatos(const char *nombreArch, struct Plato *&plato) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    plato=new struct Plato[CAP_BUFFER]; //se asigna con una capacidad auxiliar
    int i=0;char c;
    while (entrada >> plato[i].codigo >> c) {
        entrada.ignore(1000, ',');
        entrada >> plato[i].precio;
        i++;
    }
}

char * leerCadenaExacta(ifstream &archivo, char delimitador) {
    char buffer[CAP_BUFFER];
    archivo.getline(buffer, CAP_BUFFER, delimitador);
    if (archivo.eof()) return nullptr;
    char* cadena=new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void leerDistritos(const char *nombreArch, struct Distrito *&distrito) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    distrito=new struct Distrito[CAP_BUFFER]; //se asigna con una capacidad auxiliar
    int i=0; char c;
    while (entrada >> distrito[i].codigo >> c) {
        distrito[i].nombre=leerCadenaExacta(entrada, ',');
        entrada >> distrito[i].costoDelivery;
        i++;
    }
}

long long calcularTiempoSec(struct Hora tiempo) {
    return (tiempo.hora*3600)+(tiempo.minuto*60)+(tiempo.segundo);
}

void insertarOrdenado(struct Nodo *&lista, struct Pedido pedidoAux) {
    struct Nodo* puntero=lista;
    struct Nodo* anterior=nullptr;
    struct Nodo* nuevo;
    nuevo=new struct Nodo;

    nuevo->pedido=pedidoAux;
    long long tiempoNuevo=calcularTiempoSec(nuevo->pedido.recepcion);

    while (puntero!=nullptr) {
        long long tiempoPuntero=calcularTiempoSec(puntero->pedido.recepcion);
        if (tiempoNuevo<tiempoPuntero) break;
        anterior=puntero;
        puntero=puntero->siguiente;
    }
    nuevo->siguiente=puntero;
    if (anterior==nullptr) lista=nuevo;
    else anterior->siguiente=nuevo;
}

struct Plato * buscarPlato(struct Plato *plato, int codPlatoBuscado) {
    struct Plato *puntero=plato;
    while (puntero->codigo!=0) {
        if (puntero->codigo==codPlatoBuscado) return puntero;
        puntero++;
    }
    return nullptr;
}

struct Distrito * buscarDistrito(struct Distrito *distrito, int codDistritoBuscado) {
    struct Distrito* puntero=distrito;
    while (puntero->codigo!=0) {
        if (puntero->codigo==codDistritoBuscado) return puntero;
        puntero++;
    }
    return nullptr;
}

void acumularPlatos(ifstream &entrada, struct Plato* plato, struct Pedido &pedidoAux) {
    int codPlato, cantPedida, cantPedidosTotales=0; double subtotal=0; char c;
    while (entrada >> codPlato >> c >> cantPedida) {
        cantPedidosTotales+=cantPedida;
        struct Plato* platoEncontrado=buscarPlato(plato, codPlato);
        if (platoEncontrado!=nullptr) subtotal+=(platoEncontrado->precio*cantPedida);
        if (entrada.get()=='\n') break;
    }
    pedidoAux.subtotal=subtotal;
    pedidoAux.cantidad=cantPedidosTotales;
    if (pedidoAux.subtotal>=100) pedidoAux.costoDelivery=0;
    pedidoAux.total=pedidoAux.subtotal+pedidoAux.costoDelivery;
}

void leerPedidos(const char *nombreArch, struct Nodo *&lista, struct Plato* plato, struct Distrito* distrito) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);
    lista=nullptr;
    struct Pedido pedidoAux{};
    char c; int codDistritoEntrega;

    while (entrada >> pedidoAux.numero >> c) {
        entrada >> pedidoAux.recepcion.hora >> c >> pedidoAux.recepcion.minuto >> c >> pedidoAux.recepcion.segundo >> c;
        pedidoAux.cliente=leerCadenaExacta(entrada, ',');
        entrada >> codDistritoEntrega >> c;

        struct Distrito *distritoEncontrado=buscarDistrito(distrito, codDistritoEntrega);
        if (distritoEncontrado!=nullptr) {
            pedidoAux.distrito=new char[strlen(distritoEncontrado->nombre)+1];
            strcpy(pedidoAux.distrito, distritoEncontrado->nombre);
            pedidoAux.costoDelivery=distritoEncontrado->costoDelivery;
            acumularPlatos(entrada, plato, pedidoAux);
        }
        insertarOrdenado(lista, pedidoAux);
    }
}


//FUNCIONES PARA ELIMINAR DATOS:

void eliminarPedidos(struct Nodo *&lista, int horaL, int minL, int segL) {
    struct Nodo* puntero=lista;
    struct Nodo* anterior=nullptr;
    struct Nodo* sale;
    long long tiempoMaximo=(horaL*3600)+(minL*60)+segL;

    while (puntero!=nullptr) {
        long long tiempo=calcularTiempoSec(puntero->pedido.recepcion);
        if (tiempo<=tiempoMaximo) {
            anterior=puntero;
            puntero=puntero->siguiente;
        }
        else {
            sale=puntero;
            if (anterior==nullptr) {
                lista=puntero->siguiente;
                puntero=lista;
            }
            else {
                anterior->siguiente=puntero->siguiente;
                puntero=puntero->siguiente;
            }
            delete sale;
        }
    }
}


//FUNCIONES PARA IMPRIMIR:

void imprimirSeparador(ofstream& archivo, int n, char c) {
    for (int i = 0; i < n; i++) archivo << c;
    archivo << endl;
}

void imprimirEncabezado1(ofstream &salida) {
    imprimirSeparador(salida, ANCHO_REPORTE1, '=');
    salida << right << setw((ANCHO_REPORTE1+48)/2) << "RESTAURANTE SABOR CRIOLLO - SERVICIO DE DELIVERY" << endl;
    salida << right << setw((ANCHO_REPORTE1+52)/2) << "PEDIDOS RECIBIDOS (ORDENADOS POR HORA DE RECEPCIÓN)" << endl;
    imprimirSeparador(salida, ANCHO_REPORTE1, '=');
    salida << left << setw(8) << "Pedido" << setw(10) << "Hora" << setw(28) << "Cliente"
            << setw(22) << "Distrito" << right << setw(10) << "Cantidad" << setw(12) << "Subtotal" << endl;
    imprimirSeparador(salida, ANCHO_REPORTE1, '-');
}

void imprimirEncabezado2(ofstream &salida, int horaL, int minL, int segL) {
    imprimirSeparador(salida, ANCHO_REPORTE2, '=');
    salida << right << setw((ANCHO_REPORTE2+48)/2) << "RESTAURANTE SABOR CRIOLLO - SERVICIO DE DELIVERY" << endl;
    salida << right << setw((ANCHO_REPORTE2+19)/2) << "PEDIDOS A DESPACHAR" << endl;
    imprimirSeparador(salida, ANCHO_REPORTE2, '=');

    salida << "Hora límite de recepción: " << right << setw(2) << setfill('0') << horaL << ":"
            << setw(2) << minL << ":" << setw(2) << segL << setfill(' ') << left << endl;
    imprimirSeparador(salida, ANCHO_REPORTE2, '-');
    salida << left << setw(8) << "Pedido" << setw(10) << "Hora" << setw(28) << "Cliente"
            << setw(22) << "Distrito" << right << setw(10) << "Cantidad" << setw(12) << "Subtotal"
            << setw(10) << "Delivery" << setw(12) << "Total" << endl;
    imprimirSeparador(salida, ANCHO_REPORTE2, '-');
}

void imprimirResumen1(ofstream &salida, int totalPedidos, double costoTotal) {
    imprimirSeparador(salida, ANCHO_REPORTE1, '-');
    salida << left << setw(50) << "Total de pedidos recibidos:" << right << setw(12) << totalPedidos << endl;
    salida << left << setw(50) << "Monto total por platos (subtotales):" << right << setw(12) << costoTotal << endl;
    imprimirSeparador(salida, ANCHO_REPORTE1, '-');
}

void imprimirResumen2(ofstream &salida, int totalPedidos, double costoTotal, double montoTotalDelivery,
    double montoTotalCobrar) {
    imprimirSeparador(salida, ANCHO_REPORTE2, '-');
    salida << left << setw(50) << "Pedidos a despachar:" << right << setw(12) << totalPedidos << endl;
    salida << left << setw(50) << "Monto total por platos (subtotales):" << right << setw(12) << costoTotal << endl;
    salida << left << setw(50) << "Monto total por delivery:" << right << setw(12) << montoTotalDelivery << endl;
    salida << left << setw(50) << "Monto total por cobrar:" << right << setw(12) << montoTotalCobrar << endl;
    imprimirSeparador(salida, ANCHO_REPORTE2, '=');
}


//FUNCIONES PARA GENERAR REPORTES:

void abrirArchEscritura(const char* nombreArch, ofstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void generarReporte1(const char *nombreArch, struct Nodo *lista) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    imprimirEncabezado1(salida);

    struct Nodo *puntero=lista;
    int totalPedidos=0; double costoTotal=0;

    while (puntero) {
        salida << left << setw(8) << puntero->pedido.numero << right << setw(2) << setfill('0')
                << puntero->pedido.recepcion.hora << ":" << setw(2) << puntero->pedido.recepcion.minuto
                << ":" << setw(2) << puntero->pedido.recepcion.segundo << setfill(' ') << left << setw(2)
                << "" << setw(28) << puntero->pedido.cliente << setw(22) << puntero->pedido.distrito
                << right << setw(10) << puntero->pedido.cantidad << fixed << setprecision(2) << setw(12)
                << puntero->pedido.subtotal << endl;
        totalPedidos++;
        costoTotal+=puntero->pedido.subtotal;
        puntero=puntero->siguiente;
    }
    imprimirResumen1(salida, totalPedidos, costoTotal);
}

void generarReporte2(const char *nombreArch, struct Nodo *lista, int horaL, int minL, int segL) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    imprimirEncabezado2(salida, horaL, minL ,segL);

    struct Nodo *puntero=lista;
    int totalPedidos=0; double costoTotal=0, montoTotalDelivery=0, montoTotalCobrar=0;

    while (puntero) {
        salida << left << setw(8) << puntero->pedido.numero << right << setw(2) << setfill('0')
                << puntero->pedido.recepcion.hora << ":" << setw(2) << puntero->pedido.recepcion.minuto
                << ":" << setw(2) << puntero->pedido.recepcion.segundo << setfill(' ') << left << setw(2)
                << "" << setw(28) << puntero->pedido.cliente << setw(22) << puntero->pedido.distrito
                << right << setw(10) << puntero->pedido.cantidad << fixed << setprecision(2) << setw(12)
                << puntero->pedido.subtotal << setw(10) << puntero->pedido.costoDelivery << setw(12)
                << puntero->pedido.total << endl;
        totalPedidos++;
        costoTotal+=puntero->pedido.subtotal;
        montoTotalDelivery+=puntero->pedido.costoDelivery;
        montoTotalCobrar+=puntero->pedido.total;
        puntero=puntero->siguiente;
    }
    imprimirResumen2(salida, totalPedidos, costoTotal, montoTotalDelivery, montoTotalCobrar);
}


//FUNCIONES PARA LIBERAR MEMORIA:

void eliminarLista(struct Nodo *&lista, struct Distrito* &distrito) {
    struct Distrito* punteroD=distrito;
    while (punteroD->codigo!=0) {
        delete [] punteroD->nombre;
        punteroD++;
    }
    delete [] distrito;

    struct Nodo* sale;
    while (lista) {
        sale = lista;
        lista=lista->siguiente;
        delete [] sale->pedido.cliente;
        delete [] sale->pedido.distrito;
        delete sale;
    }
}
