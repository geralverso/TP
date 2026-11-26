//
// Created by PC on 25/11/2026.
//

#include "FuncionesAuxiliares.h"
#include "NodoDoble.h"

void abrirArchLectura(const char *nombreArch, ifstream &archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
}

void insertarAlFinal(struct NodoDoble *&lista, char nuevoDato) {
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
        while (puntero->siguiente!=nullptr) puntero=puntero->siguiente;
        nuevo->anterior=puntero;
        puntero->siguiente=nuevo;
    }
}

void leerPalabra(const char *nombreArch, struct NodoDoble *&lista) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    lista=nullptr;
    char c;
    while (entrada >> c) {
        insertarAlFinal(lista, c);
    }
}

bool esPalindromo(struct NodoDoble *lista) {
    struct NodoDoble *pIzquierda=lista; //ya está al inicio
    struct NodoDoble *pDerecha=lista; //debe estar al final

    if (lista==nullptr or lista->siguiente==nullptr) return true;

    while (pDerecha->siguiente!=nullptr) {
        pDerecha=pDerecha->siguiente; //recorre el pDerecha hasta el final
    }

    while (pIzquierda!=pDerecha and pDerecha->siguiente!=pIzquierda) {
        if (pIzquierda->dato!=pDerecha->dato) return false;
        pIzquierda=pIzquierda->siguiente;
        pDerecha=pDerecha->anterior;
    }
    return true;
}

void imprimirEnOrden(struct NodoDoble* lista) {
    struct NodoDoble *puntero=lista;
    cout << "Palabra leida de izquierda a derecha: ";
    while (puntero) {
        cout << puntero->dato;
        puntero=puntero->siguiente;
    }
}

void imprimirEnOrdenInverso(struct NodoDoble* lista) {
    struct NodoDoble *puntero=lista;
    if (puntero) {
        while (puntero->siguiente!=nullptr) puntero=puntero->siguiente;
    }
    cout << "\nPalabra leida de derecha a izquierda: ";
    while (puntero) {
        cout << puntero->dato;
        puntero=puntero->anterior;
    }
}

void mostrarEnPantalla(struct NodoDoble *lista) {
    imprimirEnOrden(lista);
    imprimirEnOrdenInverso(lista);
    cout << "\nEs palindromo: ";
    if (esPalindromo(lista)) cout << "true";
    else cout << "false";
}

void eliminarLista(struct NodoDoble *&lista) {
    struct NodoDoble* sale;
    while (lista) {
        sale=lista;
        lista=lista->siguiente;
        delete sale;
    }
}
