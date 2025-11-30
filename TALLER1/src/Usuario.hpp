//
// Created by GRINGO on 30/11/2025.
//

#ifndef EXAMEN2_USUARIO_HPP
#define EXAMEN2_USUARIO_HPP
#include "LibroEnSuPoder.hpp"
struct Usuario {
    int dni;
    char *nombre;
    char categoria;
    double calificacion;
    struct LibroEnSuPoder *libros;
    int cantLibros;
};
#endif //EXAMEN2_USUARIO_HPP