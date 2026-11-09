//
// Created by aml on 7/11/2026.
//

#ifndef EJERCICIO_ESTRUCTURAS_VEHICULO_H
#define EJERCICIO_ESTRUCTURAS_VEHICULO_H

#include "Captura.h"
#include "Infraccion.h"

struct Vehiculo {
    int codigo;
    char categoria;
    int dniPropietario;
    char* placa;
    int arrAniosRevisiones[4];
    int cantRevisiones;
    struct Captura arrCapturasValidas[10];
    int cantCapturasValidas;
    struct Captura arrCapturasInvalidas[10];
    int cantCapturasInvalidas;
    struct Infraccion arrInfracciones[2];
};

#endif //EJERCICIO_ESTRUCTURAS_VEHICULO_H
