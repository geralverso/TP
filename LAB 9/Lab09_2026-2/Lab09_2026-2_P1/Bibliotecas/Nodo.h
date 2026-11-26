//
// Created by PC on 25/11/2026.
//

#ifndef LAB09_2026_2_P1_NODO_H
#define LAB09_2026_2_P1_NODO_H

#include "Pedido.h"

struct Nodo {
    struct Pedido pedido;
    struct Nodo *siguiente;
};

#endif //LAB09_2026_2_P1_NODO_H
