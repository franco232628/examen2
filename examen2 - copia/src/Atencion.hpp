//
// Created by GRINGO on 30/11/2025.
//

#ifndef EXAMEN2_ATENCION_HPP
#define EXAMEN2_ATENCION_HPP
#include "Plato.hpp"
#include "Comentario.hpp"

struct Atencion {
    int codigo;
    struct Plato *platos_atendidos;
    int cantidad_platos;
    double total_venta;
    int hora;
    struct Comentario *comentarios;
    int cantidad_comentarios;
};



#endif //EXAMEN2_ATENCION_HPP