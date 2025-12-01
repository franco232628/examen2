//
// Created by Diego Zapata on 30/11/2025.
//

#ifndef EXAMEN_ESPECIAL_25_1_COMENTARIO_H
#define EXAMEN_ESPECIAL_25_1_COMENTARIO_H
struct Comentario {
    char *texto;
    char *preProcesado;
    struct Palabra palabras[20];
    int cantPalabras;
    int polaridadTotal;
};

#endif //EXAMEN_ESPECIAL_25_1_COMENTARIO_H