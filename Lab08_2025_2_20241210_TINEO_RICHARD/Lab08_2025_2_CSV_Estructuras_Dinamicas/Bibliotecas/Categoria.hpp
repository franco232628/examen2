//
// Created by aml on 17/11/2025.
//

#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP
#include "Reproduccion.hpp"

struct Categoria {
    char *codigo;
    char *nombre;
    char *descripcion;
    struct Reproduccion *reproducciones; //15
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};


#endif //CATEGORIA_HPP
