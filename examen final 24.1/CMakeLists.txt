cmake_minimum_required(VERSION 4.0)
project(examen_final_24_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(examen_final_24_1 main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Cliente.h
        Bibliotecas/Venta.h
        Bibliotecas/Libreria.h
        Bibliotecas/Libro.h)
