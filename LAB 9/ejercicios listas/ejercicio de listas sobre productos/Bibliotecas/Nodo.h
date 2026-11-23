//
// Created by PC on 17/11/2026.
//

#ifndef EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_NODO_H
#define EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_NODO_H

#include "Producto.h"

struct Nodo {
    struct Producto producto;
    struct Nodo* siguiente;
};

#endif //EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_NODO_H
