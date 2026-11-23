//
// Created by PC on 18/11/2026.
//

#ifndef EJERCICIO_COURIER_ENTREGA_H
#define EJERCICIO_COURIER_ENTREGA_H

#include "Fecha.h"

struct Entrega {
    char estado;
    struct Fecha fechaEntrega;
    int cantDiasDemora;
};

#endif //EJERCICIO_COURIER_ENTREGA_H
