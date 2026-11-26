//
// Created by PC on 25/11/2026.
//

#ifndef LAB09_2026_2_P1_PEDIDO_H
#define LAB09_2026_2_P1_PEDIDO_H

#include "Hora.h"

struct Pedido {
    int numero;
    struct Hora recepcion;
    char* cliente;
    char* distrito;
    int cantidad;
    double subtotal;
    double costoDelivery;
    double total;
};

#endif //LAB09_2026_2_P1_PEDIDO_H
