cmake_minimum_required(VERSION 4.3)
project(ejercicio_estructuras)

set(CMAKE_CXX_STANDARD 20)

add_executable(ejercicio_estructuras main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.h
        Bibliotecas/Vehiculo.h
        Bibliotecas/Captura.h
        Bibliotecas/Infraccion.h
)
