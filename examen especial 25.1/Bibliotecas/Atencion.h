//
// Created by Diego Zapata on 30/11/2025.
//

#ifndef EXAMEN_ESPECIAL_25_1_ATENCION_H
#define EXAMEN_ESPECIAL_25_1_ATENCION_H
struct Atencion {
    int codigo;
    struct Plato platosAtendidos[20];
    int cantPlatos;
    double totalVenta;
    int hora;
    struct Comentario comentarios[20];
    int cantComentarios;
};
#endif //EXAMEN_ESPECIAL_25_1_ATENCION_H