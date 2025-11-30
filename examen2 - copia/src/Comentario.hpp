//
// Created by GRINGO on 30/11/2025.
//

#ifndef EXAMEN2_COMENTARIO_HPP
#define EXAMEN2_COMENTARIO_HPP
#include "Palabra.hpp"
struct Comentario {
    char *texto;
    char *pre_procesado;
    struct Palabra palabras[20];
    int cantidad_palabras;
    int polaridad_total;
};





#endif //EXAMEN2_COMENTARIO_HPP