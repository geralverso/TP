//
// Created by PC on 17/11/2026.
//

#ifndef EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_PRODUCTO_H
#define EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_PRODUCTO_H

#include "Venta.h"

struct Producto {
    int codigo;
    char* descripcion;
    double precio;
    int stockInicial;
    struct Venta arrVentas[20];
    int numVentas;
    int unidadesVendidas;
    double montoVendido;
    int stockFinal;
};

#endif //EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_PRODUCTO_H
