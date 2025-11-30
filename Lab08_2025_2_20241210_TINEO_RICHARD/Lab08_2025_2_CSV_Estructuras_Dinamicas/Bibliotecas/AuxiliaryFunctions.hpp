//
// Created by aml on 17/11/2025.
//

#ifndef AUXILIARYFUNCTIONS_HPP
#define AUXILIARYFUNCTIONS_HPP

#include "Utils.hpp"

void leerCategoria(struct Categoria * arrCategoria,
    int &cantidadCategorias, const char * file_name);
void open_read( ifstream & input, const char * file_name);
char * read_str( ifstream & input, char delim, int MAX);
void imprimirReporteDePruebaDeCategorias(struct Categoria * arrCategoria,
    int cantidadCategorias, const char * file_name, const char * file_nameReprod,
    const char * file_nameOrden, const char * file_nameComentario, int cond);



void open_print( ofstream & output, const char * file_name);
void print_line( ofstream & output, int size, char caract);
void leerStreams(struct Categoria * arrCategoria, int cantidadCategorias, const char * file_name);
int buscarCategoria(struct Categoria * arrCategoria, int cantidadCategorias,char * code_categoria);
double read_double( ifstream & input);
int read_time( ifstream & input);
void print_time( ofstream & output, int duracion);
void swapC( struct Categoria & categoria1,  struct Categoria & categoria2);
void leerComentarios(struct Categoria * arrCategoria,
    int cantidadCategorias, const char * file_name);
void agregarDescripcion(struct Categoria * &arrCategoria,
    int cantidadCategorias, char * canal_leido,
     char * descripcion_leido);
void ordenarPorNombre(struct Categoria * &arrCategoria, int cantidadCategorias);

void printHeaders( ofstream & output, int cantidadCategorias, struct Categoria * arrCategoria, int posicion);


#endif //AUXILIARYFUNCTIONS_HPP
