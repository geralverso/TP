cmake_minimum_required(VERSION 4.3)
project(Lab09_2026_2_P1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab09_2026_2_P1 main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Hora.h
        Bibliotecas/Plato.h
        Bibliotecas/Distrito.h
        Bibliotecas/Pedido.h
        Bibliotecas/Nodo.h)
