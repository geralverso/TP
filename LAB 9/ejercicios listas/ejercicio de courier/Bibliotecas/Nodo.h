//
// Created by PC on 18/11/2026.
//

#ifndef EJERCICIO_COURIER_NODO_H
#define EJERCICIO_COURIER_NODO_H

#include "Envio.h"

struct Nodo {
    struct Envio envio;
    struct Nodo* siguiente;
};

#endif //EJERCICIO_COURIER_NODO_H
