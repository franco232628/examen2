//
// Created by GRINGO on 30/11/2025.
//

#ifndef EXAMEN2_LIBRO_HPP
#define EXAMEN2_LIBRO_HPP
#include "UsuarioConElLibro.hpp"
struct Libro {
    char *codigo;
    char *titulo;
    char *autor;
    int cantidad;
    double precio;
    struct UsuarioConElLibro *usuarios;
    int cantUsuarios;
};
#endif //EXAMEN2_LIBRO_HPP