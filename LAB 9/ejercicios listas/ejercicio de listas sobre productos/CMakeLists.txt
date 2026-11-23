cmake_minimum_required(VERSION 4.3)
project(ejercicio_de_listas_sobre_productos)

set(CMAKE_CXX_STANDARD 20)

add_executable(ejercicio_de_listas_sobre_productos main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.h
        Bibliotecas/Venta.h
        Bibliotecas/Producto.h
        Bibliotecas/Nodo.h)
