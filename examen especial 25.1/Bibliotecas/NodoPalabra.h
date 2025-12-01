//
// Created by Diego Zapata on 30/11/2025.
//

#ifndef EXAMEN_ESPECIAL_25_1_NODOPALABRA_H
#define EXAMEN_ESPECIAL_25_1_NODOPALABRA_H
#include  "Palabra.h"
struct NodoPalabra {
    struct Palabra dato;
    struct NodoPalabra *next;
};

#endif //EXAMEN_ESPECIAL_25_1_NODOPALABRA_H