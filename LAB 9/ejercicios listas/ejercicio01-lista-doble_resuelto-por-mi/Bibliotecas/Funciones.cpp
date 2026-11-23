//
// Created by PC on 21/11/2026.
//

#include "Funciones.h"

void abrirArchLectura(const char* nombreArch, ifstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

//lo ultimo leido es lo q se pone primero en la lista
void insertarAlInicio(struct NodoDoble *&lista, int nuevoDato) {
    struct NodoDoble *nuevo;
    nuevo = new struct NodoDoble;

    nuevo->dato=nuevoDato; //se asigna el nuevo dato
    nuevo->anterior=nullptr; //si es el 1er nodo, su puntero anterior es nullptr
    nuevo->siguiente=lista; //el puntero siguiente apunta al 1er elemento de la lista

    if (lista!=nullptr) lista->anterior=nuevo; //si la lista aun no termina, el siguiente nodo es nuevo
    lista=nuevo; //la lista empieza a apuntar a ese nuevo Dato
}

void insertarAlFinal(struct NodoDoble *&lista, int nuevoDato) {
    struct NodoDoble *puntero=lista;
    struct NodoDoble *nuevo;
    nuevo=new struct NodoDoble;

    nuevo->dato=nuevoDato;
    nuevo->siguiente=nullptr;

    if (lista==nullptr) {
        nuevo->anterior=nullptr;
        lista=nuevo;
    }
    else {
        while (puntero->siguiente!=nullptr) {
            puntero=puntero->siguiente;
        }
        nuevo->anterior=puntero;
        puntero->siguiente=nuevo;
    }
}

void insertarOrdenado(struct NodoDoble *&lista, int nuevoDato) {
    struct NodoDoble *puntero=lista;
    struct NodoDoble *ant=nullptr;
    struct NodoDoble *nuevo;
    nuevo=new struct NodoDoble;

    nuevo->dato=nuevoDato;

    while (puntero!=nullptr and nuevoDato>puntero->dato) {
        ant=puntero;
        puntero=puntero->siguiente;
    }

    nuevo->siguiente=puntero;
    nuevo->anterior=ant;

    if (puntero!=nullptr) puntero->anterior=nuevo;
    if (ant==nullptr) lista=nuevo;
    else ant->siguiente=nuevo;
}

void cargarNumeros(const char *nombreArch, struct NodoDoble *&lista) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    int datoLeido;
    lista=nullptr;

    while (entrada >> datoLeido) {
        insertarOrdenado(lista, datoLeido);
    }
}

void eliminarDeLaLista(struct NodoDoble *&lista, int datoAEliminar) {
    struct NodoDoble *puntero=lista;

    while (puntero!=nullptr and datoAEliminar>puntero->dato) {
        puntero=puntero->siguiente;
    }

    if (puntero!=nullptr and puntero->dato==datoAEliminar) {
        if (puntero->anterior==nullptr) lista=puntero->siguiente;
        else puntero->anterior->siguiente=puntero->siguiente;
        if (puntero->siguiente!=nullptr) puntero->siguiente->anterior=puntero->anterior;
        delete puntero;
    }
}

void eliminarMenores(struct NodoDoble *&lista, int datoMinimo) {
    struct NodoDoble *puntero=lista;
    struct NodoDoble *sale;

    while (puntero) {
        if (puntero->dato>=datoMinimo) {
            puntero=puntero->siguiente;
        }
        else {
            sale=puntero;
            if (puntero->anterior==nullptr) lista=puntero->siguiente;
            else puntero->anterior->siguiente=puntero->siguiente;
            if (puntero->siguiente!=nullptr) puntero->siguiente->anterior=puntero->anterior;
            puntero=puntero->siguiente;
            delete sale;
        }
    }
}

void imprimirEnOrden(ofstream &salida, struct NodoDoble *lista) {
    struct NodoDoble *puntero=lista;
    salida << left << setw(20) << "EN ORDEN:";
    while (puntero) {
        salida << left << setw(4) << puntero->dato;
        puntero=puntero->siguiente;
    }
}

void imprimirEnOrdenInverso(ofstream &salida, struct NodoDoble *lista) {
    struct NodoDoble *puntero=lista;
    salida << "\n" << setw(20) << "EN ORDEN INVERSO:";
    if (puntero){
        while (puntero->siguiente!=nullptr) { //va al ultimo nodo
            puntero=puntero->siguiente;
        }
    }
    while (puntero) {
        salida << left << setw(4) << puntero->dato;
        puntero=puntero->anterior; //de ese ultimo nodo, empieza a retroceder
    }
}

void abrirArchEscritura(const char* nombreArch, ofstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void generarReporte(const char *nombreArch, struct NodoDoble *lista) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    imprimirEnOrden(salida, lista);
    imprimirEnOrdenInverso(salida, lista);
}

void eliminarLista(struct NodoDoble *&lista) {
    struct NodoDoble *sale;
    while (lista) {
        sale=lista;
        lista=lista->siguiente;
        delete sale;
    }
}
