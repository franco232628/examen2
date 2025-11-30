cmake_minimum_required(VERSION 4.0)
project(examen2)

set(CMAKE_CXX_STANDARD 17)

add_executable(examen2 main.cpp
        src/Utils.hpp
        src/AuxiliaryFunctions.cpp
        src/AuxiliaryFunctions.hpp
        src/Palabra.hpp
        src/Comentario.hpp
        src/Plato.hpp
        src/Atencion.hpp)
