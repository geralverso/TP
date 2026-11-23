cmake_minimum_required(VERSION 4.3)
project(ejercicio_courier)

set(CMAKE_CXX_STANDARD 20)

add_executable(ejercicio_courier main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.h
        Bibliotecas/Fecha.h
        Bibliotecas/Persona.h
        Bibliotecas/Tarifa.h
        Bibliotecas/Destino.h
        Bibliotecas/Entrega.h
        Bibliotecas/Envio.h
        Bibliotecas/Nodo.h
        Bibliotecas/TotalPorZona.h
        Bibliotecas/Resumen.h)
