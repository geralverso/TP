//
// Created by PC on 18/11/2026.
//

#ifndef EJERCICIO_COURIER_ENVIO_H
#define EJERCICIO_COURIER_ENVIO_H

#include "Fecha.h"
#include "Persona.h"
#include "Entrega.h"
#include "Destino.h"

struct Envio {
    char* codigo;
    struct Fecha fechaRegistro;
    struct Persona remitente;
    struct Persona destinatario;
    struct Destino destino;
    double peso;
    double costo;
    struct Entrega entrega;
};

#endif //EJERCICIO_COURIER_ENVIO_H
