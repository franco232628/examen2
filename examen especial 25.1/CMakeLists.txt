cmake_minimum_required(VERSION 4.0)
project(examen_especial_25_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(examen_especial_25_1 main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Palabra.h
        Bibliotecas/Comentario.h
        Bibliotecas/Plato.h
        Bibliotecas/Atencion.h
        Bibliotecas/NodoPalabra.h
        Bibliotecas/NodoPlato.h
        Bibliotecas/NodoAtencion.h)
