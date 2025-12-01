//
// Created by Diego Zapata on 30/11/2025.
//

#ifndef EXAMEN_FINAL_24_1_LIBRO_H
#define EXAMEN_FINAL_24_1_LIBRO_H
struct Libro {
    char *codigo;
    char *titulo;
    char *autor;
    double precio;
    struct Libreria *librerias;
    int cantLibrerias;
    double totalVentas;
    int unidadesVendidas;
    int cantBuenasCal;
    int cantMalasCal;
    double sumaBuenasCal, sumaMalasCal;
};
#endif //EXAMEN_FINAL_24_1_LIBRO_H