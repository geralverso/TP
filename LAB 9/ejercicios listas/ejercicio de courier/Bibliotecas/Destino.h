//
// Created by PC on 18/11/2026.
//

#ifndef EJERCICIO_COURIER_DESTINO_H
#define EJERCICIO_COURIER_DESTINO_H

#include "Tarifa.h"

struct Destino {
    int codigoDistrito;
    char* nombreDistrito;
    char zona;
    struct Tarifa tarifa;
};

#endif //EJERCICIO_COURIER_DESTINO_H
