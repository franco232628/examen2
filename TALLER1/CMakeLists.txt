cmake_minimum_required(VERSION 4.0)
project(examen2)

set(CMAKE_CXX_STANDARD 17)

add_executable(examen2 main.cpp
        src/Utils.hpp
        src/AuxiliaryFunctions.cpp
        src/AuxiliaryFunctions.hpp
        src/UsuarioConElLibro.hpp
        src/LibroEnSuPoder.hpp
        src/Libro.hpp
        src/Usuario.hpp
)
