//
// Created by PC on 17/11/2026.
//

#include "Funciones.h"


//FUNCIONES PARA LEER, CARGAR, CREAR, MODIFICAR:

void abrirArchLectura(const char* nombreArch, ifstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
}

char* leerCadenaExacta(ifstream &archivo, char delimitador) {
    char buffer[CAP_BUFFER];
    archivo.getline(buffer,CAP_BUFFER, delimitador);
    if (archivo.eof()) return nullptr;
    char* cadena=new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

void insertarOrdenado(struct Nodo *&lista, struct Producto prodNuevo) {
    struct Nodo* puntero=lista;
    struct Nodo* anterior=nullptr;
    struct Nodo* nuevo;
    nuevo=new struct Nodo;

    nuevo->producto=prodNuevo;
    while (puntero!=nullptr and prodNuevo.codigo>(puntero->producto.codigo)) {
        anterior=puntero;
        puntero=puntero->siguiente;
    }
    nuevo->siguiente=puntero;
    if (anterior==nullptr) lista=nuevo;
    else anterior->siguiente=nuevo;
}

void crearCatalogo(const char *nombreArch, struct Nodo *&lista) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    struct Producto prodAux{};
    lista=nullptr;
    char c;
    while (entrada >> prodAux.codigo >> c) {
        prodAux.descripcion=leerCadenaExacta(entrada, ',');
        entrada >> prodAux.precio >> c >> prodAux.stockInicial;
        insertarOrdenado(lista, prodAux);
    }
}

struct Nodo* buscarCodigo(struct Nodo *lista, int codigoBuscado) {
    struct Nodo *puntero=lista;
    while (puntero and puntero->producto.codigo!=codigoBuscado) {
        puntero=puntero->siguiente;
    }
    return puntero; //retorna el nodo si se encuentra, o nullptr si no existe
}

void eliminarDeLaLista(struct Nodo *&lista, int codigoBuscado) {
    struct Nodo *puntero=lista;
    struct Nodo *anterior=nullptr;

    while (puntero and (puntero->producto.codigo)<codigoBuscado) {
        anterior=puntero;
        puntero=puntero->siguiente;
    }
    if (puntero and (puntero->producto.codigo)==codigoBuscado) {
        if (anterior==nullptr) {
            lista=lista->siguiente;
        }
        else {
            anterior->siguiente=puntero->siguiente;
        }
        delete puntero;
    }
}

void eliminarSinVentas(struct Nodo *&lista) {
    struct Nodo *puntero=lista;
    struct Nodo *anterior=nullptr;
    struct Nodo *sale;

    while (puntero) {
        if (puntero->producto.numVentas>0) {
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

void agregarProdNuevos(const char *nombreArch, struct Nodo *&lista) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    struct Producto prodNuevoAux{};
    char c;
    while (entrada >> prodNuevoAux.codigo >> c) {
        prodNuevoAux.descripcion=leerCadenaExacta(entrada, ',');
        entrada >> prodNuevoAux.precio >> c >> prodNuevoAux.stockInicial;

        struct Nodo* codigoEncontrado=buscarCodigo(lista, prodNuevoAux.codigo);
        if (codigoEncontrado==nullptr) { //si el codigoNuevo no se encuentra en la lista, se agrega
            insertarOrdenado(lista, prodNuevoAux);
        }
    }
}

void retirarProductos(const char *nombreArch, struct Nodo *&lista) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    int codigo;
    while (entrada >> codigo) {
        struct Nodo* codigoEncontrado=buscarCodigo(lista, codigo);
        if (codigoEncontrado!=nullptr) { //si el codigo a retirar se encuentra en la lista, se elimina
            eliminarDeLaLista(lista, codigo);
        }
    }
}

void cargarVentas(const char *nombreArch, struct Nodo *&lista) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    int fecha, cantidad, codigo; char c;
    while (entrada >> codigo >> c) {
        entrada >> fecha >> c >> cantidad;

        struct Nodo* codigoEncontrado=buscarCodigo(lista, codigo);
        if (codigoEncontrado!=nullptr) {
            codigoEncontrado->producto.arrVentas[codigoEncontrado->producto.numVentas].fecha=fecha;
            codigoEncontrado->producto.arrVentas[codigoEncontrado->producto.numVentas].cantidad=cantidad;
            codigoEncontrado->producto.numVentas++;
            codigoEncontrado->producto.montoVendido+=codigoEncontrado->producto.precio*cantidad;
            codigoEncontrado->producto.unidadesVendidas+=cantidad;
            codigoEncontrado->producto.stockFinal=codigoEncontrado->producto.stockInicial-
                codigoEncontrado->producto.unidadesVendidas;
        }
    }
}


//FUNCIONES PARA IMPRIMIR:

void imprimirSeparador(ofstream &archivo, char c, int n) {
    for (int i=0; i<n; i++) archivo << c;
    archivo << endl;
}

void imprimirEncabezado(ofstream &archivo, const char *titulo) {
    archivo << titulo << endl;
    imprimirSeparador(archivo, '=', ANCHO_REPORTE);
    archivo << left << setw(10) << "CÓDIGO" << setw(25) << "DESCRIPCIÓN" << setw(10) << "PRECIO" << "STOCK\n";
    imprimirSeparador(archivo, '=', ANCHO_REPORTE);
}

void imprimirFecha(ofstream &archivo, int fecha) {
    int anio=fecha/10000, mes=(fecha%10000)/100, dia=fecha%100;
    archivo << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/" << setw(4) << anio
            << setfill(' ');
}

void imprimirVentas(struct Nodo *puntero, ofstream &salida) {
    if (puntero->producto.numVentas>0) {
        salida << right << setw(10) << "Ventas:" << endl;
        for (int i=0; i<(puntero->producto.numVentas); i++) {
            salida << setw(3) << " ";
            imprimirFecha(salida, puntero->producto.arrVentas[i].fecha);
            salida << setw(8) << " " << puntero->producto.arrVentas[i].cantidad << " u." << endl;
        }
        salida << left << setw(3) << " " << "Unidades vendidas = " << setw(5) << puntero->producto.unidadesVendidas
                << "Monto = " << setw(10) << fixed << setprecision(2) << puntero->producto.montoVendido
                << "Stock final = " << puntero->producto.stockFinal;
        if (puntero->producto.stockFinal<=5) salida << " << REPONER\n";
        else salida << endl;
    }
}

void imprimirResumenFinal(ofstream &salida, int cantProdTotal, int cantUnidadesTotal, double montoTotal) {
    salida << left << setw(25) << "Cantidad de productos:" << cantProdTotal << endl;
    salida << left << setw(25) << "Unidades vendidas:" << cantUnidadesTotal << endl;
    salida << left << setw(25) << "Monto total vendido:" << fixed << setprecision(2) << montoTotal << endl;
}


//FUNCIONES PARA GENERAR REPORTES:

void abrirArchEscritura(const char* nombreArch, ofstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
}

void generarReporte(const char *nombreArch, struct Nodo *lista, int tipoReporte) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    if (tipoReporte==1) imprimirEncabezado(salida, "CATÁLOGO INICIAL");
    else if (tipoReporte==2) imprimirEncabezado(salida, "CATÁLOGO ACTUALIZADO (ALTAS Y RETIROS)");
    else if (tipoReporte==3) imprimirEncabezado(salida, "VENTAS POR PRODUCTO");
    else if (tipoReporte==4) imprimirEncabezado(salida, "CATÁLOGO FINAL (SIN PRODUCTOS SIN VENTAS)");

    int cantProdTotal=0, cantUnidadesTotal=0; double montoTotal=0.0;
    struct Nodo* puntero=lista;
    while (puntero) {
        salida << left << setw(9) << puntero->producto.codigo << setw(25) << puntero->producto.descripcion
                << fixed << setprecision(2) << setw(10) << puntero->producto.precio
                << puntero->producto.stockInicial << endl;

        imprimirVentas(puntero, salida);
        cantProdTotal++;
        cantUnidadesTotal+=puntero->producto.unidadesVendidas;
        montoTotal+=puntero->producto.montoVendido;
        puntero=puntero->siguiente; //esto siempre va al final
        imprimirSeparador(salida, '-', ANCHO_REPORTE);
    }
    if (tipoReporte==4) imprimirResumenFinal(salida, cantProdTotal, cantUnidadesTotal, montoTotal);
}


//FUNCIONES PARA LIBERAR MEMORIA:

void liberarMemoria(struct Nodo *&lista) {
    struct Nodo* sale;
    while (lista) {
        sale = lista;
        lista = lista->siguiente;
        delete [] sale->producto.descripcion; //borra el arreglo dinamico descripcion
        delete sale; //borra los nodos de la lista
    }
}